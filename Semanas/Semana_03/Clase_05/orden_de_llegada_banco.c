#include<pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ticket_dist = 0, display = 0; // ticket distrib. & display


void ocupar(){
    pthread_mutex_lock(&m);
    int my_num = ticket_dist++;
    while(my_num != ticket_dist)
        pthread_cond_wait(&cond, &m);
    pthread_mutex_unlock(&m);
}


void desocupar(){
    pthread_mutex_lock(&m);
    display++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&m);
}

