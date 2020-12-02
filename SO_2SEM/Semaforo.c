#include "Semaforo.h"
#include <pthread.h>
#include <semaphore.h>
#include "Jogadores.h"
#include <stdlib.h>
#include <stdio.h>

#define N 200 // Maximum items a producer can produce or a consumer can consume

sem_t empty;
sem_t full;
pthread_mutex_t mutex = 1;

void *producer(void *prod_info)
{  
    while(*(prod_info -> ptr_quemVenceu) == 0){
        sem_wait(&empty); //down empty
        pthread_mutex_lock(&mutex); //down mutex
        enter_item(prod_info -> ptr_placar, prod_info -> ptr_j2); //using critical region
        pthread_mutex_unlock(&mutex); //up mutex
        sem_post(&full); //up full
    }
}

void *consumer(void *cons_info)
{  
    while(*(cons_info -> ptr_quemVenceu) == 0){
        sem_wait(&full); //down full
        pthread_mutex_lock(&mutex); //down mutex
        remove_item(cons_info -> ptr_placar, cons_info -> ptr_j1); //using critical region
        pthread_mutex_unlock(&mutex); //up mutex
        sem_post(&empty); //up empty
    }
}

void init_all_sem()
{
    sem_init(&empty, 0, N); //shared with all threads and with initial value N
    sem_init(&full, 0, 0); //shared with all threads and with initial value 0
    pthread_mutex_init(&mutex, NULL); //By default, the initial state of *mutex will be "initialized and unlocked"
}

void destroy_all_sem()
{
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}

void enter_item(float* scoreboard, int* item)
{
    updateScoreboard(scoreboard, item, 1);
}

void remove_item(float* scoreboard, int* item)
{
    updateScoreboard(scoreboard, item, -1);
}
