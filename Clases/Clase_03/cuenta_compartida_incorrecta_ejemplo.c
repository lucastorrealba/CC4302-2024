// Ejemplo cuenta unica
#include<pthread.h>
#include<stdio.h>
int saldo_cuenta = 100000;

int consultar(){return saldo_cuenta;};
void modificar(int nuevo_saldo){ saldo_cuenta = nuevo_saldo;};

int autorizar(int monto){
    int res = 0;
    int saldo = consultar();
    if (saldo-monto>=0){
        int nuevo_saldo = saldo-monto;
        modificar(nuevo_saldo);
        res = 1;
    }
    return res;
}

void *thread_func(void *ptr){
    autorizar(1);
    return NULL;
}

int main(int argc, char **argv){
    int p = 10000;
    pthread_t t[p];
    for (int i=0; i<p; i++)
        pthread_create(&t[i], NULL, thread_func, NULL);
    for (int i=0; i<p; i++)
        pthread_join(t[i], NULL);
    printf("Saldo final (deberia ser 90000): %d\n", saldo_cuenta);
    return 0;
}



