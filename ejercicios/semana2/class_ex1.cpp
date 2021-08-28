#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

#define is_this_a_variable 3.14159

namespace FISI2028{
    float sum = 1.5;
}

float glb_x = 0;
int glb_i = 0;

// & me pasa la referencia de MEMORIA RAM de las variables a y b
void swap(float &a, float &b){ // Cuidado: mutar los scopes fuera de ellas!
    // swap con variable temporal
    // float a_temp = a;
    // a = b;
    // b = a_temp;

    // swap sin crear una variable temporal
    a = a + b;
    b = a - b;
    a = a - b;
}

int digits(int a){
    // dividir por 10
    // loop en el cual divido por 10 y miro el valor de a
    // continuar dividiendo hasta que el valor sea 0
    // el operador / solo funciona entre los mismos tipos de
    // variables
    int contador = 0;

    // 0 es un edge case
    if (a == 0){
        return 1;
    }
    // negativos es otro edge case
    if (a < 0){
        // a = -a;
        a = abs(a);
    }
    // la implementacion no contempla que a = 0
    while(a > 0){ // loop sin terminacion definida
        a = a / 10;
        contador ++;
    }
    return contador;
}

bool is_digit_in_number(int d, int a){
    // esta d en a?
    int digit;
    if (a == 0 && d == 0){
        return true;
    }
    while (a > 0){
        digit = a % 10;
        if(digit == d){
            return true;
        }
        a /= 10;
    }
    return false;
}

void unique_digits(int a){ // pasa por valor!
    // residuo
    // 134 -> 134 mod 10 = 4
    // 134 -> (134 / 10) mod 10 = 3
    // 134 -> (134 / 100) mod 10 = 1

    int i;
    int contador = 0;
    if (a < 0){
        a = -a;
    }
    for(i = 0; i <= 9; i++){
        if(is_digit_in_number(i,a))
            contador++;
    }
    cout<<"el numero de digitos unicos de a="<<a<<" es "<<contador<<endl;
    // return contador;
}

int main(void){
    // scope: main (funcion)
    int j = 0;
    cout<<"Value of 'j'? "<<j<<endl;
    cout<<"Value of 'FISI2028::sum'? "<<FISI2028::sum<<endl;

    float a = 1;
    float b = 3.3;
    cout<<setprecision(9)<< a << ", " << b << endl;
    swap(a,b); // pasar por referencia
    cout<<"finalmente... "<< a << ", " << b << endl;

    cout<<"valor de 'j'? "<<j<<endl;
    cout<<"cuantos digitos tiene 'j'? "<< digits(j) << endl;

    cout << "prueba a la funcion is_digit_in_number()" << endl;
    cout << is_digit_in_number(2,2010) << endl;

    unique_digits(j); // j = 0 es un 'edge' case
    return 0;
}
