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
Jogador* jogadorInicial(Jogador *jogador1, Jogador *jogador2) {
    // inicialização de variaveis
    int maiorDupla1 = -1, maiorDupla2 = -1; 
    int soma1 = 0, soma2 = 0;

    for(int i = 0; i < jogador1->qntPecas; i++){
        // identificar a soma das peças de cada jogador
        soma1 += jogador1->maoJogador[i].ladoEsquerdo + jogador1->maoJogador[i].ladoDireito;
        soma2 += jogador2->maoJogador[i].ladoEsquerdo + jogador2->maoJogador[i].ladoDireito;
        // identificar se os jogadores possuem duplas / carrossel
        if(jogador1->maoJogador[i].ladoEsquerdo == jogador1->maoJogador[i].ladoDireito){
            maiorDupla1 = i;
        }
        if(jogador2->maoJogador[i].ladoEsquerdo == jogador2->maoJogador[i].ladoDireito){
            maiorDupla2 = i;
        }
    }

    // Caso não tenha dupla, as duplas continuarão com -1.
    if(maiorDupla1 != -1 && maiorDupla2 != -1){
        if(jogador1->maoJogador[maiorDupla1].ladoEsquerdo > jogador2->maoJogador[maiorDupla2].ladoEsquerdo){
            return jogador1;
        } else if(jogador2->maoJogador[maiorDupla2].ladoEsquerdo > jogador1->maoJogador[maiorDupla1].ladoEsquerdo){
            return jogador2;
        }
    }

    if(soma1 > soma2){
        return jogador1;
    } else if (soma2 > soma1){
        return jogador2;
    } else {
        // identificar o maior numero presente nas peças entre os jogadores
        int maiorNum1 = jogador1->maoJogador[0].ladoEsquerdo + jogador1->maoJogador[0].ladoDireito;
        int maiorNum2 = jogador2->maoJogador[0].ladoEsquerdo + jogador2->maoJogador[0].ladoDireito;

        for(int i = 1; i < jogador1->qntPecas; i++){
            if(jogador1->maoJogador[i].ladoEsquerdo + jogador1->maoJogador[i].ladoDireito > maiorNum1){
                maiorNum1 = jogador1->maoJogador[i].ladoEsquerdo + jogador1->maoJogador[i].ladoDireito;
            }
            if(jogador2->maoJogador[i].ladoEsquerdo + jogador2->maoJogador[i].ladoDireito > maiorNum2){
                maiorNum2 = jogador2->maoJogador[i].ladoEsquerdo + jogador2->maoJogador[i].ladoDireito;
            }
        }

        if(maiorNum1 > maiorNum2){
            return jogador1;
        } else {
            return jogador2;
        }
    }
}

// Função responsável por printar na tela o jogador da vez e seus status
void printaTurno(Jogador *jogador, EstadoJogo *estado) {
    // Peças disponíveis na mão do jogador
    printf("Mao do %s:\n", jogador->nomeJogador);
    for (int i = 0; i < jogador->qntPecas; i++) {
        printf("[%d|%d] ", jogador->maoJogador[i].ladoEsquerdo, jogador->maoJogador[i].ladoDireito);
    }

    // Peças disponíveis na mesa
    printf("\n\nPecas disponiveis na mesa:\n");
    for (int i = 0; i < estado->qntPecasMesa; i++) {
        printf("[%d|%d] ", estado->pecasMesa[i].ladoEsquerdo, estado->pecasMesa[i].ladoDireito);
    }

    // Informações adicionais
    printf("\n\nInformacoes adicionais:\n");
    printf("Pecas disponiveis na mao do adversario: %d\n", 28 - (jogador->qntPecas + estado->qntPecasMesa));
    printf("Pecas disponiveis para compra: %d\n", estado->pecasDisponiveis);
}

// Função com as 3 oções de jogadas por jogador
void escolhaOpcao(Jogador *jogador, EstadoJogo *estado) {
    int opcao;
    printf("Opcoes disponiveis:\n");
    printf("1. Jogar Peca\n2. Comprar Peca\n3. Passar Vez\n");  
    printf("Escolha uma das opcoes acima.\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            jogarPeca(jogador, estado);
            break;
        case 2:
            comprarPeca(jogador, estado);
            break;
        case 3:
            passarVez(jogador, estado);
            break;
        default:
            printf("Opção inserida é inválida!\n\n");
            escolhaOpcao(jogador, estado);  
    }
}

// Jogar peça escolhida
void jogarPeca(Jogador *jogador, EstadoJogo *estado){
    int escolha;
    int indicePeca;

    printf("Pecas disponiveis para a jogada:\n");
    printaTurno(jogador, estado); // Chamada da função criada anteriormente para exibir dados na tela.
    printf("Escolha a peca a ser jogada: (0-%d)\n", jogador->qntPecas - 1); // indice varia de 0 - numero de pecas
    scanf("%d", &indicePeca);

    if(indicePeca < 0 || indicePeca >= jogador->qntPecas){
        printf("Indice inserido foi invalido");
        return; // Preciso fazer uma manutenção do código para que ele mostre novamente para o usuario
    }

    printf("Insira o lado no qual queira jogar(0 - esquerda e 1 - direita): ");
    scanf("%d", &escolha);

    if(escolha != 0 && escolha != 1){
        printf("O lado escolhido foi invalido.");
        return; // Preciso fazer uma manutenção do código para que ele mostre novamente para o usuario
    }

    // Atualização da struct jogador com a ultima jogada;
    jogador->ultimaJogada = jogador->maoJogador[indicePeca];
    jogador->ladoPeca = escolha;

    // Adicionar uma peça em um dos lados da mesa atual;
    if(escolha == 0){
        estado->pecasMesa[estado->qntPecasMesa++] = jogador->ultimaJogada;
    } else {
        estado->pecasMesa[estado->qntPecasMesa] = jogador->ultimaJogada;
        estado->qntPecasMesa++;
    }

    // Removendo peca da mão do jogador
    for(int i = indicePeca; i < jogador->qntPecas - 1; i++){
        jogador->maoJogador[i] = jogador->maoJogador[i + 1];
    }
    jogador->qntPecas--;

    estado->ultimaJogada = jogador->ultimaJogada;
    estado->ladoPeca = jogador->ladoPeca;
    estado->pecasDisponiveis--;

    // Alternar para o próximo jogador
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
void salvarJogo(EstadoJogo *estado, char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "wb"); // txt ou binario

    if(file == NULL){
        printf("O arquivo nao foi encontrado com sucesso.\n");
        return;
    }

    fwrite(estado, sizeof(EstadoJogo), 1, file);

    fclose(file);
}

// Função que carrega o estado jogo de um arquivo bin
void carregarJogo(EstadoJogo *estado, char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "rb"); // txt ou binario

    if(file == NULL){
        printf("Erro ao encontrar o arquivo inserido.\n");
        return;
    }

    fread(estado, sizeof(EstadoJogo), 1, file);

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
    estado.jogadorDaVez = 0;
    estado.totalJogadores = 2;

    while (condicaoFimJogo(jogadores, &estado) == false) {
        printf("Turno do jogador: %s\n", jogadores[estado.jogadorDaVez].nomeJogador);
        printaTurno(&jogadores[estado.jogadorDaVez], &estado);

        escolhaOpcao(&jogadores[estado.jogadorDaVez], &estado);
    }
}

// Identificar se a partida terminou e qual jogador continua.
bool condicaoFimJogo(Jogador *jogadores, EstadoJogo *estado) {
    for (int i = 0; i < estado->totalJogadores; i++) {
        printf("\nJogador %s - Pecas: %d\n", jogadores[i].nomeJogador, jogadores[i].qntPecas);
        if (jogadores[i].qntPecas <= 0) {
            printf("O jogador %s venceu o jogo!\n", jogadores[i].nomeJogador);
            return true;
        }
    }
    return false;
}

int menuJogo(){
    int opcaoMenu;
    
    printf("MENU - GAME\n");
    printf("Insira uma das 3 opcoes abaixo:\n");
    printf("1. Iniciar\n2. Carregar Jogo\n3. Sair\n");
    scanf("%d", &opcaoMenu);

    return opcaoMenu;
}

int main() {
    int opcaoMenuJogo;

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
            // carregarJogo();
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