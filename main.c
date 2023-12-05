#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "domino.h"
#include "jogo.h"

void menujogo(){
    printf("MENU - GAME\n");
    printf("Insira uma das 3 opções abaixo:\n");
    printf("1. Iniciar\n2. Carregar Jogo\n3. Sair");
}

int main(){
    printf("--DOMINO`S GAME--");
    
    // A partir daqui ocorre a inicialização do jogo com a declaração de variáveis essênciais 
    Peca pecas[MAX_PECAS];
    Jogador jogadores[2];

    identificaJogadores(jogadores, 2);
    criacaoPecas(pecas);
    embaralharPecas(pecas);
    distribuicaoPecas(pecas, &jogadores[0], NUM_PECAS);
    distribuicaoPecas(pecas + NUM_PECAS, &jogadores[1], NUM_PECAS);
    
    EstadoJogo estado;
    estado.qntPecasMesa = 0;
    estado.pecasDisponiveis = MAX_PECAS - (2 * NUM_PECAS); // 28 peças - as 14 dos 2 jogadores
    estado.jogadorDaVez = 0;
    estado.totalJogadores = 2;

    return 0;
}