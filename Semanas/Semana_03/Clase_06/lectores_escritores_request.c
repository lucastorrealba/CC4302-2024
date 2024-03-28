#include<pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int writing = 0; 
int readers = 0;


typedef struct{
    int ready;
    pthread_cond_t w;
    Kind kind;
} Request;

Queue q;


void enqueue(Kind kind){
    Request req = {0, PTHREAD_COND_INITIALIZER, kind};
    put(q, &req);
    while(!req.ready)
        pthread_cond_wait(&req.w, &m);
}



void wakeup(){
    Request *pr = peek(q);
    if(pr==NULL)
        return;
    if(pr->kind==WRITER){
        writing = 1;
        pr->ready = 1;
        pthread_cond_signal(&pr->w);
        get(q);
    }
    else{
        do{// readers
            readers++;
            pr->ready=1;
            pthread_cond_signal(&pr->w);
            get(q);
            pr = peek(q);
            }while(pr!= NULL && pr->kind==READER);
    }
}

void enterRead(){
    pthread_mutex_lock(&m);
    if (!writing && emptyQueue(q))
        readers++;
    else
        enqueue(READER);
    pthread_mutex_unlock(&m);
}
void exitRead(){
    pthread_mutex_lock(&m);
    readers--;
    if (readers == 0)
        wakeup();
    pthread_mutex_unlock(&m);

}

void enterWrite(){
    pthread_mutex_lock(&m);
    if (!writing && readers == 0)
        writing = 1;
    else
        enqueue(WRITER);
    pthread_mutex_unlock(&m);
}

void exitWrite(){
    pthread_mutex_lock(&m);
    writing = 0;
    wakeup();
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