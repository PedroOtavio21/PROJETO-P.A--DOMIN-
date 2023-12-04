#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domino.h"

void identificaJogadores(Jogador jogadores[], int numJogadores){
    printf("Olá! Insira o nome dos dois jogadores.\n");
    for(int i = 0; i < 2; i++){
        printf("Jogador %d: ", i + 1);
        fgets(jogadores[i].nomeJogador, 50, stdin);
    }
}

void criarPecas(){
    
}

