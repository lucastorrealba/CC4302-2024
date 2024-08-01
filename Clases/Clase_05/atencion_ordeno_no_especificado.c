#include<pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int busy = 0;

void ocupar(){
    pthread_mutex_lock(&m);
    while(busy)
        pthread_cond_wait(&cond, &m);
    busy = 1;
    pthread_mutex_unlock(&m);
}


void desocupar(){
    pthread_mutex_lock(&m);
    busy = 0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&m);
}

