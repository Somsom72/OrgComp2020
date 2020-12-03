/**
 * \file Jogadores.h
 * \brief Conteúdo relacionado às threads dos jogadores.
 */

#ifndef JOGADORES_H
#define JOGADORES_H

#include "defines.h"

typedef struct {
	char nome[MAX_CARACTERES];
	int *ptr_buffer;
} Jogador;

/** 
 * \brief Struct de entrada das threads. 
 */
typedef struct {
	Jogador jogador1;
	Jogador jogador2;
	float *ptr_placar;
	int *ptr_quemVenceu;
} Infos;

Jogador inicializarJogador(char* nome, int* ptr_buffer);

Infos inicializarInfos(Jogador j1, Jogador j2, float* ptr_placar, int* ptr_quemVenceu);

/**
 * \brief Descarrega buffer do jogador, atualizando o placar para a direção especificada.
 * 
 * Implementa "inércia", ou seja, o placar prefere se mover para a direção em que atualmente aponta. 
 * Assume valor de placar em [-100, 100].
 * 
 * \param placar Ponteiro para valor do placar a ser atualizado.
 * \param j Ponteiro para inteiro que representa um jogador (mais precisamente, seu "buffer").
 * \param fator_inercia Float positivo que indica a intensidade da inérica.
 * \param dir -1 caso deseje atualizar para a direção negativa, 1 caso contrário. 
 * 
 * \return 0 caso operação bem-sucedida; 1 caso contrário.
*/
int atualizaPlacar(float *placar, int *j, float fator_inercia, int dir);

/**
 * \brief Dado um placar, determina se há algum vencedor. 
 * 
 * Assume valor de placar em [-DURACAO_DO_JOGO, DURACAO_DO_JOGO].
 * 
 * \param placar Valor do placar.
 * 
 * \return 0 caso ninguém venceu ainda; 1 caso jogador 1 (lado negativo); 2 caso jogador 2 (lado positivo).
*/
int determinaVencedor(float placar);

#endif