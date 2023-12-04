#ifndef DOMINO_H
#define DOMINO_H

#define MAX_PECAS 28
#define NUM_PECAS 7
// Criação de estruturas para a reutilização ao decorrer do trabalho
typedef struct{
    int ladoEsquerdo;
    int ladoDireito;
} Peca;

typedef struct{
    char nomeJogador[50];
    Peca maoJogador[NUM_PECAS];
    int qntPecas;
} Jogador;
/*
typedef struct{
    Peca pecasMesa[MAX_PECAS];
    int qntPecasMesa;
    int jogadorDaVez;
} EstadoJogo;
*/

void identificaJogadores(Jogador jogadores[], int numJogadores);
void criacaoPecas(Peca pecas[]);
void distribuicaoPecas(Peca pecas[], Jogador *jogador, int numPecas);
void imprimirJogo();

Jogador* jogadorInicial(Jogador *jogador1, Jogador *jogador2);

void salvarJogo();
void carregarJogo();

#endif