#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "domino.h"
#include "jogo.h"

int menuJogo(){
    int opcaoMenu;
    
    printf("MENU - GAME\n");
    printf("Insira uma das 3 opcoes abaixo:\n");
    printf("1. Iniciar\n2. Carregar Jogo\n3. Sair");
    scanf("%d", &opcaoMenu);

    return opcaoMenu;
}

int main(){
    int opcaoMenujogo;
    printf("--DOMINO`S GAME--");

    do{
        opcaoMenujogo = menujogo();

        switch(opcaoMenujogo){
            case 1:
                printf("Inicializando jogo...\n");
                // iniciarJogo();
                break;
            case 2:
                printf("Carregando jogo...\n");
                // carregarJogo(estado, nomeArquivo);
                break;
            case 3:
                printf("Ok. Saindo do menu...");
                break;
            default:
                printf("Opcao inserida eh invalida!!!\n");
        }
    } while (opcaoMenujogo != 3);
    
    // A partir daqui ocorre a inicialização do jogo com a declaração de variáveis essênciais 
    Peca pecas[MAX_PECAS];
    Jogador jogadores[2];

    // Funções base inicializadas no domino.h
    identificaJogadores(jogadores, 2);
    criacaoPecas(pecas);
    embaralharPecas(pecas);
    distribuicaoPecas(pecas, &jogadores[0], NUM_PECAS);
    distribuicaoPecas(pecas + NUM_PECAS, &jogadores[1], NUM_PECAS);
    
    // Structs estado do jogo com variaveis importantes para o jogo
    EstadoJogo estado;
    estado.qntPecasMesa = 0;
    estado.pecasDisponiveis = MAX_PECAS - (2 * NUM_PECAS); // 28 peças - as 14 dos 2 jogadores
    estado.jogadorDaVez = 0;
    estado.totalJogadores = 2;

    //while(){
        
    //}
    return 0;
}