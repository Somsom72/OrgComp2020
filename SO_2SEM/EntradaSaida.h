/**
 * \file EntradaSaida.h
 * \brief Conteúdo relacionado a captar entradas e formatar saídas.
 */

#ifndef ENTRADASAIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define boolean unsigned char
#define TRUE 1
#define FALSE 0

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) (((a)<(b))?(a):(b))

#define ENTRADASAIDA_H

#define DURACAO_DO_JOGO 100

#define TAMANHO_DA_CORDA 15

void captaEntrada(int* pontuacao1, int* pontuacao2);

void imprimeSaida(float* placar);

#endif