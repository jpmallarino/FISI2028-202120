#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace fisi2028{
    unsigned int n = 0;
    double e_x = 0;
    double e_x2 = 0;
    double e_x3 = 0;
    double e_x4 = 0;

    void accumulate(double x){  }
}

int main(void){
    // scope: main (funcion)
    // ofstream file; // Output File STREAM

    // file.open("output.txt");

    // int n_el = 0;

    // file.close();


    // crear un programa que me lee un numero determinado de entradas
    int entradas = 10;
    int vals[10]; // crea un vector de 10 componentes en memoria de MAIN
    // esto es una declaracion estatica

    int *vals2 = nullptr; // crea un apuntador a memoria vals2

    vals2 = new int[1000]; // me devuelve una direccion de memoria con 1000 enteros reservados!


    cout << "el numero de entradas es: "<<entradas<<endl;
    int i = 0;
    for (i = 0; i < entradas; i++){
        cout<<"ingrese entrada "<<i+1 << " " ;cin >> vals2[i];
    }

    cout << vals2[0] << ", ";
    cout << vals2[1] << ", ";
    cout << vals2[2] << ", ";
    cout << vals2[3] << ", ";
    cout << vals2[4] << ", ";
    cout << vals2[5] << ", ";
    cout << vals2[6] << ", ";
    cout << vals2[7] << ", ";
    cout << vals2[8] << ", ";
    cout << vals2[9] << endl;

    cout << "un elemento extrano " << vals2[999] << endl;

    delete [] vals2; vals2 = nullptr; // Segmentation Fault!
    return 0;
}
