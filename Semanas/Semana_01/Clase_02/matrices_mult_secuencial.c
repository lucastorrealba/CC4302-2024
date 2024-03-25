#include<stdlib.h>

typedef double **Matriz;

Matriz nuevaMatriz(int n, int m){
    double **filas = malloc(n*sizeof(double*));
    for (int i = 0; i < n; i++)
        filas[i] = malloc(m*sizeof(double)); 
    return filas;
}

void mult(Matriz a, Matriz b, Matriz c, int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            double res = 0.0;
            for(int k = 0; k < n ; k++)
                res += a[i][k]*b[k][j];
            c[i][j] = res;
        }
    }
}
int main(int argc, char **argv){
    return 0;
}
