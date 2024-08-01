#include<pthread.h>
#include<semaphore.h>
typedef struct {} Item;

typedef struct {
    int in, out, size;
    Item **array;
    sem_t empty, full;
} Buffer;

Buffer *nuevoBuffer(int size){
    Buffer *buf = (Buffer *) malloc(sizeof(Buffer));
    buf->size = size;
    buf->in=buf->out=0;
    buf->array = (Item **) malloc(size*sizeof(Item *));
    sem_init(&buf->empty, 0, size);
    sem_init(&buf->full, 0, 0);
    return buf;
}

Item *get(Buffer *buf){
    sem_wait(&buf->full);
    Item *item = buf->array[buf->out];
    buf->out = (buf->out + 1)% buf->size;
    sem_post(&buf->empty);
    return item;
}

void put(Buffer *buf, Item *item){
    sem_wait(&buf->empty);
    buf->array[buf->in] = item;
    buf->in = (buf->in + 1) % buf->size;
    sem_post(&buf->full);
}