#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domino.h"

// --------Função para identificar os dois jogadores da partida.---------
void identificaJogadores(Jogador jogadores[], int numJogadores){
    printf("Olá! Insira o nome dos jogadores participantes.\n");
    for(int i = 0; i < numJogadores; i++){
        printf("Jogador %d: ", i + 1);
        fgets(jogadores[i].nomeJogador, 50, stdin);
        fflush(stdin);
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
void distribuicaoPecas(Peca pecas[], Jogador *jogador, int numPecas){
    for(int i = 0; i < numPecas; i++){
        jogador->maoJogador[i] = pecas[i];
    }
}

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

void escolhaJogador(Jogador *jogador, EstadoJogo *estado){
    int opcao;
    printf("Opções disponíveis:\n");
    printf("1. Jogar Peça\n2. Comprar Peça\n3.Passar Vez");

    printf("\nEscolha uma das opções acima.\n");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
            // jogarPeça;
            break;
        case 2:
            // Comprar peça;
            break;
        case 3:
            // Passar vez;
            break;
        default:
            printf("Opção inserida é invalida!\n");
    }
}

void jogarPeça(Jogador *jogador, EstadoJogo *estado){
    
}