#include<stdlib.h>
#include<pthread.h>

typedef double **Matriz;
typedef struct{
    Matriz a, b, c;
    int n, ini, fin;
} Args;

Matriz nuevaMatriz(int n, int m){
    double **filas = malloc(n*sizeof(double*));
    for (int i = 0; i < n; i++)
        filas[i] = malloc(m*sizeof(double)); 
    return filas;
}

void mult(Matriz a, Matriz b, Matriz c, int n, int ini, int fin){
    for(int i = ini; i < fin ; i++){
        for(int j = 0; j < n; j++){
            double res = 0.0;
            for(int k = 0; k < n ; k++)
                res += a[i][k]*b[k][j];
            c[i][j] = res;
        }
    }
}

void *mult_thread(void *ptr){
    Args *arg = ptr;
    mult(arg->a, arg->b, arg->c, arg->n, arg->ini, arg->fin);
    return NULL;
}

void mult_paralela(Matriz a, Matriz b, Matriz c, int n, int p){
    pthread_t t[p];
    Args array[p];
    int index = 0;
    int k = n % p;
    for (int i = 0; i < p; i++){
        Args *arg = &array[i];
        arg->a=a; arg->b=b; arg->c=c; arg->n=n;
        arg->ini = index;
        index += n/p;
        if(i < k)
            index++;
        arg->fin = index;
        pthread_create(&t[i], NULL, mult_thread, arg);
    }
    
    for (int i = 0; i < p; i++)
        pthread_join(t[i], NULL);

}

int main(int argc, char **argv){
    return 0;
}
