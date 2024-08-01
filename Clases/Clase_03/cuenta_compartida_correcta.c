#include<pthread.h>
typedef struct 
{ 

} Diccionario; 
Diccionario nuevoDiccionario(){
    Diccionario d;
    return d;
};
int consultar(Diccionario dicc, int cuenta){return 0;};
void modificar(Diccionario dicc, int cuenta, int nuevo_saldo){};

Diccionario dicc;
pthread_mutex_t m;

void init(){
    dicc = nuevoDiccionario();
    pthread_mutex_init(&m, NULL);

}

int autorizar(int cuenta, int monto){
    int res = 0;
    pthread_mutex_lock(&m);
    // Inicio seccion critica
    int saldo = consultar(dicc, cuenta);
    if (saldo-monto>=0){
        int nuevo_saldo = saldo-monto;
        modificar(dicc, cuenta, nuevo_saldo);
        res = 1;
    }
    // Fin seccion critica
    pthread_mutex_unlock(&m);
    return res;
}

int main(int argc, char **argv){
    init();
    return 0;
}



