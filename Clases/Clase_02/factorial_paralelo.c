#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct{
    int i, j;
    double res;
} Args;

double mult(int i, int j){
    double res = 1.0;
    for(int k=i; k<=j; k++)
        res = res * k;
    return res;
}

double factorial(int n){
    return mult(1, n);
}

void *mult_thread(void *ptr){
    Args *a1 = (Args *) ptr;
    a1->res = mult(a1->i, a1->j);
    return NULL;
}

int main(int argc, char **argv){
    int n = atoi(argv[1]);
    int h = (n+1)/2;
    pthread_t t1, t2;
    
    Args a1 = {1, h, 0.0};
    Args a2 = {h+1, n, 0.0};
    pthread_create(&t1, NULL, mult_thread, &a1);
    pthread_create(&t2, NULL, mult_thread, &a2);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("factorial(%d)=%g\n", n, a1.res * a2.res);
    return 0;
}
