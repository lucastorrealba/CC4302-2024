#include<pthread.h>
typedef struct {
} Queue;
void put(Queue *q, void *ptr){}
void *get(Queue *q){return NULL;}
int emptyQueue(Queue *q){return 0;}

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int busy = 0;
Queue *q;

typedef struct {
    int ready;
    pthread_cond_t cond;
} Request;

void ocupar(){
    pthread_mutex_lock(&m);
    if(!busy){
        busy = 1;
    }
    else{
        Request req = {0, PTHREAD_COND_INITIALIZER};
        put(q, &req);
        while (!req.ready)
            pthread_cond_wait(&req.cond, &m);
    }
    pthread_mutex_unlock(&m);
}


void desocupar(){
    pthread_mutex_lock(&m);
    if (emptyQueue(q)){
        busy = 0;
    }
    else{
        Request *req = get(q);
        req->ready = 1; 
        pthread_cond_signal(&req->cond);
    }
    pthread_mutex_unlock(&m);
}

