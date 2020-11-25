#include "Semaforo.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define N 100 // Maximum items a producer can produce or a consumer can consume

sem_t empty;
sem_t full;
pthread_mutex_t mutex = 1;

void *producer(void *pno)
{   
    int item;
    while(true){
        produce_item(item); // Produce an new item
        sem_wait(&empty); //down empty
        pthread_mutex_lock(&mutex); //down mutex
        enter_item(item); //using critical region
        pthread_mutex_unlock(&mutex); //up mutex
        sem_post(&full); //up full
    }
}

void *consumer(void *cno)
{  
    int item;
    while(true){
        sem_wait(&full); //down full
        pthread_mutex_lock(&mutex); //down mutex
        remove_item(item); //using critical region
        pthread_mutex_unlock(&mutex); //up mutex
        sem_post(&empty); //up empty
        consume_item(item); //consume an item
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

void enter_item(int item)
{
    //to do
}

void remove_item(int item)
{

}

void produce_item(int item)
{

}

void consume_item(int item)
{

}
