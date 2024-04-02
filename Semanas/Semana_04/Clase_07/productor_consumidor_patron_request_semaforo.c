#include<semaphore.h>

typedef struct {
    int size;
    void **array;
    int in, out, cnt;
    sem_t mutex;
    Queue *prodq, *consq;
} Buffer;


Buffer *nuevoBuffer(int size) { 
    Buffer *buf= malloc(sizeof(Buffer)); 
    buf->size= size;
    buf->array= malloc(size*sizeof(void*)); 
    buf->in= buf->out= buf->cnt= 0; 
    sem_init(&buf->mutex, 0, 1); 
    buf->prodq= makeQueue(); 
    buf->consq= makeQueue(); 
    return buf;
}

void putBuf (Buffer *buf, void *item) { 
    sem_wait(&buf->mutex); // lock
    if (buf->cnt==buf->size) {
        sem_t w; // ¡Como condición! 
        sem_init(&w, 0, 0); 
        put(buf->prodq, &w); 
        sem_post(&buf->mutex); // unlock 
        sem_wait(&w); // cond wait
    }
    buf->array[buf->in]= item; 
    buf->in= (buf->in+1) % buf->size; 
    buf->cnt++;
    if (emptyQueue(buf->consq))
        sem_post(&buf->mutex); // unlock 
    else {
        sem_t *pw= get(buf->consq);
        sem_post(pw); // cond signal 
    }
}


void *getBuf(Buffer *buf) { 
    // ... ejercicio ...
}