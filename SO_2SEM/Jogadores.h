/**
 * \file Jogadores.h
 * \brief Conteúdo relacionado às threads dos jogadores.
 */

#ifndef JOGADORES_H
#define JOGADORES_H

/**
 * \brief Descarrega buffer do jogador, atualizando o placar para a direção negativa.
 * 
 * Implementa "inércia", ou seja, o placar prefere se mover para a direção em que atualmente aponta. 
 * Assume valor de placar em [-100, 100].
 * 
 * \param placar Ponteiro para valor do placar a ser atualizado.
 * \param j Ponteiro para inteiro que representa um jogador (mais precisamente, seu "buffer").
 * \param fator_inercia Float positivo que indica a intensidade da inérica.
 * 
 * \return 0 caso operação bem-sucedida; 1 caso contrário.
*/
int atualizaPlacar1(float *placar, int *j, float fator_inercia);

/**
 * \brief Descarrega buffer do jogador, atualizando o placar para a direção positiva.
 * 
 * Implementa "inércia", ou seja, o placar prefere se mover para a direção em que atualmente aponta. 
 * Assume valor de placar em [-100, 100].
 * 
 * \param placar Ponteiro para valor do placar a ser atualizado.
 * \param j Ponteiro para inteiro que representa um jogador (mais precisamente, seu "buffer").
 * \param fator_inercia Float positivo que indica a intensidade da inérica.
 * 
 * \return 0 caso operação bem-sucedida; 1 caso contrário.
*/
int atualizaPlacar2(float *placar, int *j, float fator_inercia);

/**
 * \brief Dado um placar, determina se há algum vencedor. 
 * 
 * Assume valor de placar em [-100, 100].
 * 
 * \param[in] placar Valor do placar.
 * 
 * \return 0 caso ninguém venceu ainda; 1 caso jogador 1 (lado negativo); 2 caso jogador 2 (lado positivo).
*/
int determinaVencedor(float placar);

#endif