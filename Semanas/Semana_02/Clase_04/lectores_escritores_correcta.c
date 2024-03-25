#include<pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int writing = 0; 
int readers = 0;

void enterRead(){
    pthread_mutex_lock(&m);
    while(writing)
        pthread_cond_wait(&cond, &m);
    readers++;
    pthread_mutex_unlock(&m);
}
void exitRead(){
    pthread_mutex_lock(&m);
    readers--;
    if (readers == 0)
        pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&m);

}

void enterWrite(){
    pthread_mutex_lock(&m);
    while(writing || readers > 0)
        pthread_cond_wait(&cond, &m);
    writing = 1;
    pthread_mutex_unlock(&m);
}

void exitWrite(){
    pthread_mutex_lock(&m);
    writing = 0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&m);
}

// lectores
char *query(char *k){
    char *ans;
    enterRead();
    // codigo
    exitRead();
    return ans;
}

// escritores 
void define(char *k, char *v){
    enterWrite();
    // codigo
    exitWrite();
}


int main(int argc, char **argv){
    return 0;
}