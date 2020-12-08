/**
 * \file Threads.h
 * \brief Conteúdo relacionado às threads.
 */

#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include "Jogadores.h"
#include "EntradaSaida.h"
#include "Semaforo.h"

typedef struct {
    pthread_t entrada, saida;
	pthread_t verificadorVitoria;
	pthread_t jogador1, jogador2;
} Threads;

/** 
 * \brief Thread responsável por incrementar jogador1/2 dependendo das entradas dos usuários. 
 * 
 * \param void_ptr_Infos Informações necessárias para o funcionamento das threads. 
 */
void *thread_entrada(void *void_ptr_Infos);

/** 
 * \brief Thread responsável por imprimir os gráficos de saída, dependendo do valor do placar. 
 * 
 * \param void_ptr_Infos Informações necessárias para o funcionamento das threads. 
 */
void *thread_saida(void *void_ptr_Infos);

/** 
 * \brief Thread responsável por manter a variável "quemVenceu" atualizada. 
 * 
 * \param void_ptr_Infos Informações necessárias para o funcionamento das threads. 
 */
void *thread_confereVencedor(void *void_ptr_Infos);

/** 
 * \brief Inicializa todas as threads do programa com os identificadores dados.
 * 
 * \param t Armazena os identificadores das threads. 
 * 
 * \param info Informações necessárias para o funcionamento das threads. 
 */
void criarThreads(Threads *t, Infos *info);

/** 
 * \brief Thread responsável por manter a variável "quemVenceu" atualizada. 
 * 
 * \param t Armazena os identificadores das threads. 
 */
void liberarThreads(Threads *t);

#endif