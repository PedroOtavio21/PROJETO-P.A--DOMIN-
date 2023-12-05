#ifndef JOGO_H
#define JOGO_H
#include "domino.h"

// Turnos de jogadores
Jogador* jogadorInicial(Jogador *jogador1, Jogador *jogador2);
void printaTurno(Jogador *jogador, EstadoJogo *estado);
void escolhaOpcao(Jogador *jogador, EstadoJogo *estado);

// 3 opções de jogada por jogador
void jogarPeca(Jogador *jogador, EstadoJogo *estado);
void comprarPeca(Jogador *jogador, EstadoJogo *estado);
void passarVez(Jogador *jogador, EstadoJogo *estado);

// Ponto final do jogo
void salvarJogo();
void carregarJogo();

#endif