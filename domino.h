#ifndef DOMINO_H
#define DOMINO_H

typedef struct{
    int ladoEsquerdo;
    int ladoDireito;
} Peca;

typedef struct{
    char nomeJogador[50];
    Peca maoJogador[7];
    int qntPecas;
} Jogador;

typedef struct{
    Peca pecasMesa[28];
    int qntPecasMesa;
    int jogadorDaVez;
} EstadoJogo;

void identificaJogadores();
void criarPecas();
void distribuirPecas();
int somaPecas();
int primeiraJogada();
#endif