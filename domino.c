#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"

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

