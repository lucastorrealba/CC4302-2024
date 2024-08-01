#include<pthread.h>
void comer(int i, int j){}
void pensar(){}

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t array_m[5];
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int palitos[5] = {0,0,0,0,0};

void filosofo_sol_trivial(int i){
    for(;;){
        pthread_mutex_lock(&m);
        comer(i, (i+1)%5);
        pthread_mutex_unlock(&m);
        pensar();
    }
}

void filosofo_sol_con_deadlock(int i){
    for(;;){
        pthread_mutex_lock(&array_m[i]);pthread_mutex_lock(&array_m[(i+1)%5]);
        comer(i, (i+1)%5);
        pthread_mutex_unlock(&array_m[i]);pthread_mutex_unlock(&array_m[(i+1)%5]);
        pensar();
    }
}
// no eficiente, un filósofo puede retener un palito impidiendo que un segundo filósofo 
// coma aún cuando el primer filósofo no está comiendo con ese palito.
void filosofo_sol_correcta(int i){
    for(;;){
        int minimo = min(i, (i+1)%5);
        int maximo = max(i, (i+1)%5);
        pthread_mutex_lock(&array_m[minimo]);pthread_mutex_lock(&array_m[maximo]);
        comer(i, (i+1)%5);
        pthread_mutex_unlock(&array_m[minimo]);pthread_mutex_unlock(&array_m[maximo]);
        pensar();
    }
}

void pedir(int i, int j){
    pthread_mutex_lock(&m);
    while(palitos[i] || palitos[j])
        pthread_cond_wait(&cond, &m);
    palitos[i]=palitos[j]=1;
    pthread_mutex_unlock(&m);
}
void devolver(int i, int j){
    pthread_mutex_lock(&m);
    palitos[i]=palitos[j]=0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&m);
}
// puede haber hambruna ! 
void filosofo_sol_correcta_eficiente(int i){
    for(;;){
        pedir(i, (i+1)%5);
        comer(i, (i+1)%5);
        devolver(i, (i+1)%5);
        pensar();
    }
}

int main(int argc, char **argv){
    return 0;
}
