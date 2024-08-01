void comer(int i, int j){}
void pensar(){}

void filosofo(int i){
    for(;;){
        comer(i, (i+1)%5);
        pensar();
    }
}
int main(int argc, char **argv){
    return 0;
}
