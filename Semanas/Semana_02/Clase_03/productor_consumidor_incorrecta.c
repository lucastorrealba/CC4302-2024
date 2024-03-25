#include<stdlib.h>
#include<pthread.h>
typedef struct {} Item;

typedef struct {
    int in, out, size, cnt;
    Item **array;
} Buffer;

Buffer *nuevoBuffer(int size){
    Buffer *buf = (Buffer *) malloc(sizeof(Buffer));
    buf->size = size;
    buf->in=buf->out=buf->cnt=0;
    buf->array = (Item **) malloc(size*sizeof(Item *));
    return buf;
}

Item *producir(){return NULL;}
void consumir(Item *item){}

Item *get(Buffer *buf){
    while(buf->cnt == 0)
        ; // busy waiting
    Item *item = buf->array[buf->out];
    buf->out = (buf->out + 1)% buf->size;
    buf->cnt--;
    return item;
}

void put(Buffer *buf, Item *item){
    while(buf->cnt == buf->size)
        ; // busy waiting
    buf->array[buf->in] = item;
    buf->in = (buf->in + 1) % buf->size;
    buf->cnt++;
}

void *consumidor(void *ptr){
    Buffer *buf = ptr;
    for(;;){
        Item *cuadro = get(buf);
        if (cuadro == NULL)
            break;
        consumir(cuadro);
    }
    return NULL;
}
void productor(Buffer *buf){
    for(;;){
        Item *cuadro = producir();
        put(buf, cuadro);
        if (cuadro == NULL)
            break;   
    }
}

void reproducirVideo(){
    Buffer *buf = nuevoBuffer(30*5);
    pthread_t t;
    pthread_create(&t, NULL, consumidor, buf);
    productor(buf);
    pthread_join(t, NULL);

}

int main(int argc, char **argv){
    return 0;
}