#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void){
    // crea un apuntador a memoria myvar en el que habra un entero!
    int *myvar = nullptr;
    int *ptr2 = nullptr;

    int N=0;
    cout<<"por favor ingrese el numero de elementos: ";
    cin>>N;
    // solicitemos un numero de recursos
    myvar = new int[N];

    cout<<"cual es la direccion de memoria de myvar? "<<myvar<<endl;
    // como hago para guardar informacion... []
    myvar[0] = 20;
    myvar[3] = 1984;
    // Forma mas sencilla de sacar informacion de la memoria -> vector
    cout<<"informacion guardada en [0]: "<<myvar[0]<<endl;
    cout<<"informacion guardada en [3]: "<<myvar[3]<<endl;

    // dereferenciacion *myvar == valor q hay en la direccion de memoria myvar
    cout<<"misma informacion guardada en [0]: "<<*(myvar+0)<<endl;
    cout<<"misma informacion guardada en [3]: "<<*(myvar+3)<<endl;

    cout<<"que direccion de memoria es ptr2? "<<ptr2<<endl;
    ptr2 = myvar; // copiando la direccion de memoria... NO COPIA LOS ELEMENTOS
    cout<<"direccion de memoria de N? "<<&N<<endl;
    myvar = &N; // copiando la direccion de memoria de N en myvar
    cout<<"cuantos elementos habia reservado? "<<*myvar<<endl;
    cout<<"que direccion de memoria es ptr2? "<<ptr2<<endl;
    cout<<"otra forma de halar informacion guardada en [0]: "<<*(ptr2+0)<<endl;
    cout<<"otra forma de halar informacion guardada en [3]: "<<*(ptr2+3)<<endl;

    // buena practica
    myvar = nullptr; // Segmentation Fault!
    delete [] ptr2; ptr2 = nullptr; // Segmentation Fault!
    return 0;
}
