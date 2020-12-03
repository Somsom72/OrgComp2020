/**
 * \file EntradaSaida.h
 * \brief Conteúdo relacionado a captar entradas e formatar saídas.
 */

#ifndef ENTRADASAIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENTRADASAIDA_H

/** 
 * \brief Interpreta entradas dos jogadores como acréscimos aos respectivos buffers dos objetos Jogadores. 
 * 
 * \param pontuacao1 Buffer do jogador 1. 
 * \param pontuacao2 Buffer do jogador 2. 
 */
void captaEntrada(int* pontuacao1, int* pontuacao2);

/** 
 * \brief Imprime todas as saídas enquanto a partida está ativa.  
 * 
 * \param placar Interpreta a posição da corda a partir do valor do placar atual. 
 * \param nome1 Nome do jogador 1.
 * \param nome2 Nome do jogador 2.
 */
void imprimeSaida(float* placar, char *nome1, char *nome2);

#endif