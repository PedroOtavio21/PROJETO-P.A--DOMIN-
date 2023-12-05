#include "jogo.h"

/* 
Função Mais importante inicialmente, responsável por returnar uma struct contendo o jogador
que irá iniciar a partida!
*/ 
Jogador* jogadorInicial(Jogador *jogador1, Jogador *jogador2) {
    // inicialização de variaveis
    int maiorDupla1 = -1, maiorDupla2 = -1; 
    int soma1 = 0, soma2 = 0;
    
    for(int i = 0; i < jogador1->qntPecas; i++){
        // identificar a soma das peças de cada jogador
        soma1 += jogador1->maoJogador[i].ladoEsquerdo + jogador1->maoJogador->ladoDireito;
        soma2 += jogador2->maoJogador[i].ladoEsquerdo + jogador2->maoJogador->ladoDireito;
        // identificar se os jogadores possuem duplas / carrossel
        if(jogador1->maoJogador[i].ladoEsquerdo == jogador1->maoJogador[i].ladoDireito){
            maiorDupla1 = i;
        }
        if(jogador2->maoJogador->ladoEsquerdo == jogador2->maoJogador->ladoDireito){
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

// Função responsável pelo turno da vez
void printaTurno(Jogador *jogador, EstadoJogo *estado){
    // Peças disponíveis na mão do jogador
    printf("Mao do %s:\n", jogador->nomeJogador);
    for(int i = 0; i < jogador->qntPecas; i++){
        printf("[%d|%d] ", jogador->maoJogador[i].ladoEsquerdo, jogador->maoJogador[i].ladoDireito);
    }
    // Peças disponíveis dentro da mesa
    printf("\n\nPeças disponíveis na mesa:\n");
    for(int i = 0; i < estado->qntPecasMesa; i++){
        printf("[%d|%d] ", estado->pecasMesa[i].ladoEsquerdo, estado->pecasMesa[i].ladoDireito);
    }
    // Peças disponíveis na mão do adversário
    printf("\n\nQuantidade de peças disponíveis na mão do adversário: %d", 28 - (jogador->qntPecas + estado->qntPecasMesa));
    // Peças disponíveis para uma possível compra
    printf("\n\nPeças disponíveis para compra: %d", estado->pecasDisponiveis);
}

void escolhaOpcao(Jogador *jogador, EstadoJogo *estado){
    int opcao;
    printf("Opções disponíveis:\n");
    printf("1. Jogar Peça\n2. Comprar Peça\n3.Passar Vez");

    printf("\nEscolha uma das opções acima.\n");
    scanf("%d", &opcao);

    switch(opcao){
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
            printf("Opção inserida é invalida!\n");
    }
}

void jogarPeca(Jogador *jogador, EstadoJogo *estado){
    int escolha;
    int indicePeca;

    printf("Peças disponíveis para a jogada:\n");
    printaTurno(jogador, estado); // Chamada da função criada anteriormente para exibir dados na tela.
    printf("Escolha a peça a ser jogada: (0-%d)", jogador->qntPecas - 1); // indice varia de 0 - numero de pecas
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
}

void comprarPeca(Jogador *jogador, EstadoJogo *estado){
    if(estado->pecasDisponiveis > 0){
        jogador->maoJogador[jogador->qntPecas++] = estado->pecasMesa[estado->pecasDisponiveis - 1];

        estado->pecasDisponiveis--;
        jogador->pecasCompradas;

        printf("%s comprou uma nova peca!\n", jogador->nomeJogador);
    } else {
        printf("Nao ha pecas disponiveis para compra!");
    }
}

void passarVez(Jogador *jogador, EstadoJogo *estado){
    estado->jogadorDaVez = (estado->jogadorDaVez + 1) % estado->totalJogadores;
    jogador->qntPassadasVez++;

    printf("%s passou a vez!", jogador->nomeJogador);
}