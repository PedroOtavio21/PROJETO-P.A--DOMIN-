#ifndef JOGO_H
#define JOGO_H
#include "domino.h"


// Turnos de jogadores
int jogadorInicial(Jogador jogadores[], int numJogadores) ;
void printaTurno(Jogador *jogador, EstadoJogo *estado);
void escolhaOpcao(Jogador *jogador, EstadoJogo *estado);

// 3 opções de jogada por jogador
int podeJogarPeca(Peca peca, EstadoJogo estado);
void jogarPeca(Jogador *jogador, EstadoJogo *estado);
void comprarPeca(Jogador *jogador, EstadoJogo *estado);
void passarVez(Jogador *jogador, EstadoJogo *estado);

// Ponto final do jogo
void salvarJogo(EstadoJogo *estado, const char *nomeArquivo);
void carregarJogo(EstadoJogo *estado, const char *nomeArquivo);
int menuJogo();
void iniciarJogo();
bool condicaoFimJogo(Jogador *jogadores, EstadoJogo *estado);

#endif