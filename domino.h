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
    Peca ultimaJogada;
    int ladoPeca;
    int pecasCompradas;
    int qntPassadasVez;
} Jogador;

typedef struct{
    Peca pecasMesa[MAX_PECAS];
    int qntPecasMesa;
    int pecasDisponiveis;
    Peca ultimaJogada;
    int ladoPeca; // 0 para esquerda e 1 para direita
    int jogadorDaVez;
    int totalJogadores;
} EstadoJogo;

// Inicialização do jogo
void identificaJogadores(Jogador jogadores[], int numJogadores);
void criacaoPecas(Peca pecas[]);
void distribuicaoPecas(Peca pecas[], Jogador *jogador, int numPecas);


#endif