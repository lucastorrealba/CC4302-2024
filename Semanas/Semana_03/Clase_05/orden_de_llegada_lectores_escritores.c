#include<pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int display = 0, ticket_dist = 0;
 
int readers = 0;

void enterRead(){
    pthread_mutex_lock(&m);
    int my_num = ticket_dist++;
    while(display != my_num)
        pthread_cond_wait(&cond, &m);
    readers++;
    display++;
    pthread_cond_broadcast(&cond);
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
    int my_num = ticket_dist++;
    while(readers > 0 || my_num != display)
        pthread_cond_wait(&cond, &m);
    pthread_mutex_unlock(&m);
}

void exitWrite(){
    pthread_mutex_lock(&m);
    display++;
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