#include <iostream>
#include <fstream>

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

int main(void){
    // scope: main (funcion)
    int j = 37;
    cout<<"Value of 'j'? "<<j<<endl;
    cout<<"Value of 'FISI2028::sum'? "<<FISI2028::sum<<endl;

    float a = 1;
    float b = 3.3;
    cout<< a << ", " << b << endl;
    swap(a,b);
    cout<<"finalmente... "<< a << ", " << b << endl;


    return 0;
}
