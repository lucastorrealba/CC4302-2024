int writing = 0; 
int readers = 0;

void enterRead(){
    while(writing)
        ; //  busy waiting
    readers++;
}
void exitRead(){
    readers--;

}

void enterWrite(){
    while(writing || readers > 0)
        ; // busy waiting
    writing = 1;
}

void exitWrite(){
    writing = 0;
}

// lectores
char *query(char *k){
    char *ans;
    enterRead();
    // codigo
    exitRead();
    return ans;
}

// escritores 
void define(char *k, char *v){
    enterWrite();
    // codigo
    exitWrite();
}


int main(int argc, char **argv){
    return 0;
}