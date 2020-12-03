#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include "Jogadores.h"

typedef struct {
    pthread_t entrada, saida;
	pthread_t verificadorVitoria;
	pthread_t jogador1, jogador2;
} Threads;

void *thread_entrada(void *void_ptr_Infos);
void *thread_saida(void *void_ptr_Infos);
void *thread_confereVencedor(void *void_ptr_Infos);
void criarThreads(Threads t, Infos info);
void liberarThreads(Threads t);

#endif