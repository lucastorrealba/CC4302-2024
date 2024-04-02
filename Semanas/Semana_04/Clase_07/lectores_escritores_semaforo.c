#include<semaphore.h>

sem_t mutex; // 1 ticket !!

int writing = 0; 
int readers = 0;

typedef struct{
    Kind kind;
    sem_t w;
} Request;

Queue q;

void enqueue(Kind kind){
    Request req = {kind};
    put(q, &req);
    sem_init(&req.w, 0, 0);
    sem_post(&mutex);
    sem_wait(&req.w);
}

void wakeup(){
    Request *pr = peek(q);
    if(pr==NULL)
        return;
    if(pr->kind==WRITER){
        writing = 1;
        sem_post(&pr->w); //signal
        get(q);
    }
    else{
        do{// readers
            readers++;
            sem_post(&pr->w); //signal
            get(q);
            pr = peek(q);
            }while(pr!= NULL && pr->kind==READER);
    }
}

void enterRead(){
    sem_wait(&mutex); //pthread_mutex_lock(&m);
    if (!writing && emptyQueue(q)){
        readers++;
        sem_post(&mutex); //pthread_mutex_unlock(&m);
    }
    else
        enqueue(READER);
}
void exitRead(){
    sem_wait(&mutex); //pthread_mutex_lock(&m);
    readers--;
    if (readers == 0)
        wakeup();
    sem_post(&mutex); //pthread_mutex_unlock(&m);

}

void enterWrite(){
    sem_wait(&mutex); //pthread_mutex_lock(&m);
    if (!writing && readers == 0){
        writing = 1;
        sem_post(&mutex); //pthread_mutex_unlock(&m);
    }
    else
        enqueue(WRITER);
}

void exitWrite(){
    sem_wait(&mutex); //pthread_mutex_lock(&m);
    writing = 0;
    wakeup();
    sem_post(&mutex); //pthread_mutex_unlock(&m);
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