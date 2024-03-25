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

void init(){
    dicc = nuevoDiccionario();
}

int autorizar(int cuenta, int monto){
    int res = 0;
    int saldo = consultar(dicc, cuenta);
    if (saldo-monto>=0){
        int nuevo_saldo = saldo-monto;
        modificar(dicc, cuenta, nuevo_saldo);
        res = 1;
    }
    return res;
}

int main(int argc, char **argv){
    init();
    return 0;
}



