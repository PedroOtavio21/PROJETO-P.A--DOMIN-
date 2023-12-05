#ifndef TESTE_H
#define TESTE_H

#define MAX_PECAS 28
#define NUM_PECAS 7
// Arquivo contendo dados base para serem utilizados ao decorrer do código
typedef struct{
    int ladoEsquerdo;
    int ladoDireito;
} Peca;

typedef struct{
    char nomeJogador[50];
    Peca maoJogador[NUM_PECAS];
    int qntPecas;
    Peca ultimaJogada;
    int ladoPeca; // lado no qual a peça sera jogada (esquerda ou direita)
    int pecasCompradas;
    int qntPassadasVez; // Quantidade de vezes passadas por jogador
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
void distribuicaoPecas(Peca pecas[], Jogador jogadores[], int numJogadores, int numPecas);


// Turnos de jogadores
Jogador* jogadorInicial(Jogador *jogador1, Jogador *jogador2);
void printaTurno(Jogador *jogador, EstadoJogo *estado);
void escolhaOpcao(Jogador *jogador, EstadoJogo *estado);

// 3 opções de jogada por jogador
void jogarPeca(Jogador *jogador, EstadoJogo *estado);
void comprarPeca(Jogador *jogador, EstadoJogo *estado);
void passarVez(Jogador *jogador, EstadoJogo *estado);

// Ponto final do jogo
void salvarJogo(EstadoJogo *estado, char *nomeArquivo);
void carregarJogo(EstadoJogo *estado, char *nomeArquivo);
int menuJogo();
void iniciarJogo();
bool condicaoFimJogo();


#endif