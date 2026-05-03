// implementacion basica de puntero a funciones
// se usa el mismo puntero para llamar a varias funciones

#include <iostream>

using namespace std;

int sumar (int a, int b) {
    return a + b;
}
int restar (int a, int b) {
    return a - b;
}
int multiplicar (int a, int b) {
    return a * b;
}

int main() {
    // declaramos la funcion a punteros
    int (*operation) (int, int);
    operation = sumar;
    cout<<operation(2,3)<<endl;

    operation = restar;
    cout<<operation(2,3)<<endl;

    operation = multiplicar;
    cout<<operation(2,3)<<endl;

    return 0;
}