#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "teste.h"
// Arquivo para conferir o jogo rodando e encontro de erros

// --------Função para identificar os dois jogadores da partida.---------

void identificaJogadores(Jogador jogadores[], int numJogadores) {
    printf("Ola! Insira o nome dos jogadores participantes.\n");

    for (int i = 0; i < numJogadores; i++) {
        printf("Jogador %d: ", i + 1);
        scanf("%99s", jogadores[i].nomeJogador);
    }
}

// --------------------Função para criação das 28 peças-----------------------
void criacaoPecas(Peca pecas[]){
    int k = 0;
    for(int i = 0; i <= 6; i++){
        for(int j = i; j <= 6; j++){
            pecas[k].ladoEsquerdo = i;
            pecas[k].ladoDireito = j;
            k++;
        }
    }
}

// --------Função responsável por embaralhar as peças automaticamente---------
void embaralharPecas(Peca pecas[]){
    int i, j;
    for(i = 0; i < MAX_PECAS; i++){
        j = rand() % MAX_PECAS;

        Peca temp = pecas[i];
        pecas[i] = pecas[j];
        pecas[j] = temp;
    }
}

// -------------Distribuição das peças entre os jogadores.----------------
void distribuicaoPecas(Peca pecas[], Jogador jogadores[], int numJogadores, int numPecas) {
    for (int i = 0; i < numJogadores; i++) {
        for (int j = 0; j < numPecas; j++) {
            jogadores[i].maoJogador[j] = pecas[i * numPecas + j];
        }
        jogadores[i].qntPecas = numPecas; // Atualiza a quantidade de peças para o jogador
    }

    // Ajuste para garantir que o adversário comece com 7 peças
    int adversario = (numJogadores + 1) % numJogadores;
    for (int i = numPecas; i < 2 * numPecas; i++) {
        jogadores[adversario].maoJogador[i - numPecas] = pecas[i];
    }
    jogadores[adversario].qntPecas = numPecas;
}


/* 
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
*/  

// Função para determinar o jogador Inicial
int jogadorInicial(Jogador jogadores[], int numJogadores) {
    // Inicialização de variáveis
    int maiorDupla1 = -1, maiorDupla2 = -1; 
    int soma1 = 0, soma2 = 0;

    // Verificar jogador 1
    for (int i = 0; i < jogadores[0].qntPecas; i++) {
        // Identificar a soma das peças de cada jogador
        soma1 += jogadores[0].maoJogador[i].ladoEsquerdo + jogadores[0].maoJogador[i].ladoDireito;

        // Identificar se o jogador 1 possui duplas/carrossel
        if (jogadores[0].maoJogador[i].ladoEsquerdo == jogadores[0].maoJogador[i].ladoDireito) {
            maiorDupla1 = i;
        }
    }

    // Verificar jogador 2
    for (int i = 0; i < jogadores[1].qntPecas; i++) {
        // Identificar a soma das peças de cada jogador
        soma2 += jogadores[1].maoJogador[i].ladoEsquerdo + jogadores[1].maoJogador[i].ladoDireito;

        // Identificar se o jogador 2 possui duplas/carrossel
        if (jogadores[1].maoJogador[i].ladoEsquerdo == jogadores[1].maoJogador[i].ladoDireito) {
            maiorDupla2 = i;
        }
    }

    // Caso não tenha dupla, as duplas continuarão com -1.
    if (maiorDupla1 != -1 && maiorDupla2 != -1) {
        if (jogadores[0].maoJogador[maiorDupla1].ladoEsquerdo > jogadores[1].maoJogador[maiorDupla2].ladoEsquerdo) {
            return 0; // Índice do jogador1
        } else if (jogadores[1].maoJogador[maiorDupla2].ladoEsquerdo > jogadores[0].maoJogador[maiorDupla1].ladoEsquerdo) {
            return 1; // Índice do jogador2
        }
    }

    if (soma1 > soma2) {
        return 0; // Índice do jogador1
    } else if (soma2 > soma1) {
        return 1; // Índice do jogador2
    } else {
        // Identificar o maior número presente nas peças entre os jogadores
        int maiorNum1 = jogadores[0].maoJogador[0].ladoEsquerdo + jogadores[0].maoJogador[0].ladoDireito;
        int maiorNum2 = jogadores[1].maoJogador[0].ladoEsquerdo + jogadores[1].maoJogador[0].ladoDireito;

        for (int i = 1; i < jogadores[0].qntPecas; i++) {
            if (jogadores[0].maoJogador[i].ladoEsquerdo + jogadores[0].maoJogador[i].ladoDireito > maiorNum1) {
                maiorNum1 = jogadores[0].maoJogador[i].ladoEsquerdo + jogadores[0].maoJogador[i].ladoDireito;
            }
        }

        for (int i = 1; i < jogadores[1].qntPecas; i++) {
            if (jogadores[1].maoJogador[i].ladoEsquerdo + jogadores[1].maoJogador[i].ladoDireito > maiorNum2) {
                maiorNum2 = jogadores[1].maoJogador[i].ladoEsquerdo + jogadores[1].maoJogador[i].ladoDireito;
            }
        }

        if (maiorNum1 > maiorNum2) {
            return 0; // Índice do jogador1
        } else {
            return 1; // Índice do jogador2
        }
    }
}


// Função responsável por printar na tela o jogador da vez e seus status
void printaTurno(Jogador *jogador, EstadoJogo *estado) {
    system("cls");
    // Peças disponíveis na mão do jogador
    printf("Mao do %s:\n", jogador->nomeJogador);
    for (int i = 0; i < jogador->qntPecas; i++) {
        printf("[%d|%d] - %d\n", jogador->maoJogador[i].ladoEsquerdo, jogador->maoJogador[i].ladoDireito, i);
    }

    // Peças disponíveis na mesa
    printf("\n\nPecas disponiveis na mesa:\n");
    for (int i = 0; i < estado->qntPecasMesa; i++) {
        printf("[%d|%d] ", estado->pecasMesa[i].ladoEsquerdo, estado->pecasMesa[i].ladoDireito);
    }

    // Informações adicionais
    printf("\n\nInformacoes adicionais:\n");
    printf("Pecas disponiveis na mao do adversario: %d\n", MAX_PECAS - 3 * jogador->qntPecas);
    printf("Pecas disponiveis para compra: %d\n\n", estado->pecasDisponiveis);
}

// Função com as 4 oções de jogadas por jogador
void escolhaOpcao(Jogador *jogador, EstadoJogo *estado) {
    int opcao;
    printf("Opcoes disponiveis:\n");
    printf("1. Jogar Peca\n2. Comprar Peca\n3. Passar Vez\n4. Salvar Jogo e Voltar ao menu inicial");
    printf("Escolha uma das opcoes acima.\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Voce escolheu jogar a peca!\n");
            jogarPeca(jogador, estado);
            break;
        case 2:
            printf("Voce escolheu comprar uma peca!\n");
            comprarPeca(jogador, estado);
            break;
        case 3:
            printf("Voce escolheu passar a vez!\n");
            passarVez(jogador, estado);
            break;
        case 4:
            printf("Voce escolheu salvar a partida!\n"); 
            salvarJogo(estado, NOME_ARQUIVO);
            menuJogo();
            return;
        default:
            printf("Opcao inserida eh invalida!\n\n");
            escolhaOpcao(jogador, estado);  
    }
}

int podeJogarPeca(Peca peca, EstadoJogo estado) {
    if (estado.qntPecasMesa == 0) {
        // Se a mesa estiver vazia, qualquer peça pode ser jogada
        return 1;
    }

    // Verifica se a peça pode ser jogada em qualquer um dos lados
    if (peca.ladoEsquerdo == estado.pecasMesa[0].ladoEsquerdo || 
        peca.ladoEsquerdo == estado.pecasMesa[estado.qntPecasMesa - 1].ladoDireito ||
        peca.ladoDireito == estado.pecasMesa[0].ladoEsquerdo || 
        peca.ladoDireito == estado.pecasMesa[estado.qntPecasMesa - 1].ladoDireito) {
        return 1;
    }

    return 0; // A peça não pode ser jogada
}

// Jogar peça escolhida
void jogarPeca(Jogador *jogador, EstadoJogo *estado) {
    int escolha; // 0 ou 1
    int indicePeca; 
    int girar; 

    printf("Pecas disponiveis para a jogada:\n");
    printaTurno(jogador, estado);

    printf("Escolha a peca a ser jogada (0-%d):\n", jogador->qntPecas - 1);
    scanf("%d", &indicePeca);

    if (indicePeca < 0 || indicePeca >= jogador->qntPecas) {
        printf("Indice inserido foi invalido\n");
        return;
    }

    // Girar ou nao a peca escolhida
    if (jogador->maoJogador[indicePeca].ladoEsquerdo != jogador->maoJogador[indicePeca].ladoDireito) {
        printf("Deseja girar a peca?(1 - sim e 0 - nao)\n");
        scanf("%d", &girar);

        if (girar == 1) {
            int temp = jogador->maoJogador[indicePeca].ladoEsquerdo;
            jogador->maoJogador[indicePeca].ladoEsquerdo = jogador->maoJogador[indicePeca].ladoDireito;
            jogador->maoJogador[indicePeca].ladoDireito = temp;
        }
    }

    // Verifica se a peça pode ser jogada na mesa atual
    if (!podeJogarPeca(jogador->maoJogador[indicePeca], *estado)) {
        printf("Peça inserida não pode ser utilizada na mesa.\n");
        jogarPeca(jogador, estado);
        return;
    }

    printf("Insira o lado no qual quer jogar (0 - esquerda e 1 - direita): ");
    scanf("%d", &escolha);

    if (escolha != 0 && escolha != 1) {
        printf("O lado escolhido foi invalido.\n");
        return;
    }

    // Adicionar uma peça na posição da mesa
    if (escolha == 0) {
        // Peça original passa para o próximo indice
        for (int i = estado->qntPecasMesa; i > 0; i--) {
            estado->pecasMesa[i] = estado->pecasMesa[i - 1];
        }
        estado->pecasMesa[0] = jogador->maoJogador[indicePeca];
        estado->qntPecasMesa++;
    } else {
        // Se tornará a ultima peça do vetor mesa
        estado->pecasMesa[estado->qntPecasMesa] = jogador->maoJogador[indicePeca];
        estado->qntPecasMesa++;
    }

    // Remover a peça da mão do jogador
    for (int i = indicePeca; i < jogador->qntPecas - 1; i++) {
        jogador->maoJogador[i] = jogador->maoJogador[i + 1];
    }
    jogador->qntPecas--;

    estado->ultimaJogada = jogador->maoJogador[indicePeca];
    estado->ladoPeca = escolha;
    estado->pecasDisponiveis--;

    // Passar a vez para o jogador seguinte
    passarVez(jogador, estado);
}

// Comprar peça disponível do tabuleiro
void comprarPeca(Jogador *jogador, EstadoJogo *estado) {
    if (estado->pecasDisponiveis > 0) {
        jogador->maoJogador[jogador->qntPecas++] = estado->pecasMesa[estado->pecasDisponiveis - 1];

        estado->pecasDisponiveis--;
        jogador->pecasCompradas++;

        printf("%s comprou uma nova peca!\n", jogador->nomeJogador);

        // Alternar para o próximo jogador
        passarVez(jogador, estado);
    } else {
        printf("Nao ha pecas disponiveis para compra!\n");
    }
}

// Passar a vez da jogada
void passarVez(Jogador *jogador, EstadoJogo *estado) {
    estado->jogadorDaVez = (estado->jogadorDaVez + 1) % estado->totalJogadores;
    jogador->qntPassadasVez++;

    printf("%s passou a vez!\n", jogador->nomeJogador);
}

// Função que salva o estado jogo em um arquivo bin
void salvarJogo(EstadoJogo *estado, const char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "wb");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    if (fwrite(estado, sizeof(EstadoJogo), 1, file) != 1) {
        perror("Erro ao escrever no arquivo");
    }

    fclose(file);
}
void carregarJogo(EstadoJogo *estado, const char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "rb");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    if (fread(estado, sizeof(EstadoJogo), 1, file) != 1) {
        perror("Erro ao ler do arquivo");
    }

    fclose(file);
}

void iniciarJogo() {
    // A partir daqui ocorre a inicialização do jogo com a declaração de variáveis essenciais 
    Peca pecas[MAX_PECAS];
    Jogador jogadores[2];
    // Funções base inicializadas no teste.h
    identificaJogadores(jogadores, 2);
    criacaoPecas(pecas);
    embaralharPecas(pecas);
    distribuicaoPecas(pecas, jogadores, 2, NUM_PECAS);

    int indiceJogadorInicial = jogadorInicial(jogadores, 2);

    // Após a distribuição inicial de peças
    printf("Pecas do Jogador 1: ");
    for (int i = 0; i < NUM_PECAS; i++) {
        printf("[%d|%d] ", jogadores[0].maoJogador[i].ladoEsquerdo, jogadores[0].maoJogador[i].ladoDireito);
    }
    printf("\nPecas do Jogador 2: ");
    for (int i = 0; i < NUM_PECAS; i++) {
        printf("[%d|%d] ", jogadores[1].maoJogador[i].ladoEsquerdo, jogadores[1].maoJogador[i].ladoDireito);
    }

    // Structs estado do jogo com variáveis importantes para o jogo
    EstadoJogo estado;
    estado.qntPecasMesa = 0;
    estado.pecasDisponiveis = MAX_PECAS - (2 * NUM_PECAS); // 28 peças - as 14 dos 2 jogadores
    estado.jogadorDaVez = indiceJogadorInicial;
    estado.totalJogadores = 2;

    estado.ultimaJogada.ladoEsquerdo = -1;
    estado.ultimaJogada.ladoDireito = -1;
    
    /* 
    Primeira peça jogada automaticamente na mesa:
    int jogadorPrimeiroTurno = estado.jogadorDaVez;
    printf("\nO jogador tera a primeira peca jogada na mesa\n");
    jogarPeca(&jogadores[jogadorPrimeiroTurno], &estado);
    */

    while (condicaoFimJogo(jogadores, &estado) == false) {
        printf("\n\nTurno do jogador: %s\n", jogadores[estado.jogadorDaVez].nomeJogador);
        printaTurno(&jogadores[estado.jogadorDaVez], &estado);

        escolhaOpcao(&jogadores[estado.jogadorDaVez], &estado);
    }
}

// Identificar se a partida terminou e qual jogador continua.
bool condicaoFimJogo(Jogador *jogadores, EstadoJogo *estado) {
    for (int i = 0; i < estado->totalJogadores; i++) {
        printf("\nJogador %s - Pecas: %d", jogadores[i].nomeJogador, jogadores[i].qntPecas);
        if (jogadores[i].qntPecas <= 0) {
            printf("O jogador %s venceu o jogo!\n", jogadores[i].nomeJogador);
            return true;
        }
    }
    return false;
}

int menuJogo(){
    int opcaoMenu;
    do{
    printf("MENU - GAME\n");
    printf("Insira uma das 3 opcoes abaixo:\n");
    printf("1. Iniciar\n2. Carregar Jogo\n3. Sair\n");
    scanf("%d", &opcaoMenu);

    if (opcaoMenu < 1 || opcaoMenu > 3) {
            printf("Opcao inserida eh invalida!!!\n");
    }
    
    } while (opcaoMenu < 1 || opcaoMenu > 3);
    
    if(opcaoMenu == 3){
        printf("Voce escolheu sair do jogo.\n\n");
        printf("Encerrando...");
        exit(0);
    }

    return opcaoMenu;
}

int main() {
    srand(time(NULL));
    int opcaoMenuJogo;
    EstadoJogo estado;
    printf("--DOMINO`S GAME--\n\n");

    do {
        opcaoMenuJogo = menuJogo();

        switch (opcaoMenuJogo) {
        case 1:
            printf("Inicializando jogo...\n");
            iniciarJogo();
            break;
        case 2:
            printf("Carregando jogo...\n");
            carregarJogo(&estado, NOME_ARQUIVO);
            break;
        case 3:
            printf("Ok. Saindo do menu...\n");
            break;
        default:
            printf("Opcao inserida eh invalida!!!\n");
        }
    } while (opcaoMenuJogo != 3);

    return 0;
}
