#include<semaphore.h>

sem_t pals[5];
void comer(int i, int j){}
void pensar(){}

// no eficiente, un filósofo puede retener un palito impidiendo que un segundo filósofo 
// coma aún cuando el primer filósofo no está comiendo con ese palito.
void filosofo_sol_correcta(int i){
    for(;;){
        int minimo = min(i, (i+1)%5);
        int maximo = max(i, (i+1)%5);
        //pthread_mutex_lock(&array_m[minimo]); pthread_mutex_lock(&array_m[maximo]);
        sem_wait(&pals[minimo]); sem_wait(&pals[maximo]);
        comer(i, (i+1)%5);
        //pthread_mutex_unlock(&array_m[minimo]); pthread_mutex_unlock(&array_m[maximo]);
        sem_post(&pals[minimo]); sem_post(&pals[maximo]);
        pensar();
    }
}