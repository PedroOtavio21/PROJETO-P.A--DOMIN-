#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "domino.h"
#include "jogo.h"

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