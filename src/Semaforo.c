#include "Semaforo.h"
#include <pthread.h>
#include <semaphore.h>
#include "Jogadores.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *prod_info)
{
    Infos* info = (Infos*) prod_info;

    while(*(info -> ptr_quemVenceu) == 0){
        sem_wait(&empty); //down empty
        pthread_mutex_lock(&mutex); //down mutex
        enter_item(info -> ptr_placar, info -> jogador2.ptr_buffer); //using critical region
        pthread_mutex_unlock(&mutex); //up mutex
        sem_post(&full); //up full
    }
	return NULL;
}

void *consumer(void *cons_info)
{  
    Infos* info = (Infos*) cons_info;

    while(*(info -> ptr_quemVenceu) == 0){
        sem_wait(&full); //down full
        pthread_mutex_lock(&mutex); //down mutex
        remove_item(info -> ptr_placar, info -> jogador1.ptr_buffer); //using critical region
        pthread_mutex_unlock(&mutex); //up mutex
        sem_post(&empty); //up empty
    }
	return NULL;
}

void init_all_sem()
{
    sem_init(&full, 0, 0); //shared with all threads and with initial value 0
    sem_init(&empty, 0, MAX_ITENS); //shared with all threads and with initial value N
    pthread_mutex_init(&mutex, NULL); //By default, the initial state of *mutex will be "initialized and unlocked"
}

void destroy_all_sem()
{
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}

void enter_item(int* placar, int* pontuacao)
{
    atualizaPlacar(placar, pontuacao, FATOR_INERCIA, 1);
}

void remove_item(int* placar, int* pontuacao)
{
    atualizaPlacar(placar, pontuacao, FATOR_INERCIA, -1);
}
