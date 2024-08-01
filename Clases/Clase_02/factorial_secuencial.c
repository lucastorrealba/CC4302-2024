#include<stdio.h>
#include<stdlib.h>

double mult(int i, int j){
    double res = 1.0;
    for(int k=i; k<=j; k++)
        res = res * k;
    return res;
}

double factorial(int n){
    return mult(1, n);
}

int main(int argc, char **argv){
    int n = atoi(argv[1]);
    printf("factorial(%d)=%g\n", n, factorial(n));
    return 0;
}
