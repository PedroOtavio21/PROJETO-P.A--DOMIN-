#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "jogo.h"

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
