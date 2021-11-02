#include <iostream>
#include<stdlib.h>
using namespace std;
int saltosPosibles(int n, int numsaltos, int saltos[]) {
    int posibles = 0;
    if (n == 0 || n == 1) {
        return n;
    }
    else if (n < 0) {
        return 0;
    }
    else {
        for (int i = 0; i < numsaltos; ++i) {
            posibles += saltosPosibles(n - saltos[i], numsaltos, saltos);
        }
        return posibles;
    }
}
int main()
{
    int numescalones, numsaltos, * saltos, numparadas, * paradas, posibilidades,veces;
    cout << "Digite el numero de escalones: ";
    cin >> numescalones;
    cout << "Digite el numero de posibles saltos: ";
    cin >> numsaltos;
    cout << "Ingrese el numero de escalones permitido por salto:";
    saltos= new int[numsaltos];
    for (int i = 0; i < numsaltos; ++i) {
     
        cin >> saltos[i];
        
    }
    cout << "Digite el numero de paradas obligatorias: ";
    cin >> numparadas;
    cout <<"Ingrese la ubicacion de las paradas:";
    paradas= new int[numparadas];
    for (int i = 0; i < numparadas; ++i) {
        cin >> paradas[i];
    }
    int ordenador;
    for (int i = 0; i < numparadas; i++) {
        for (int j = 0; j < numparadas - 1; j++) {
            if (*(paradas + j) > *(paradas + j + 1)) {
                ordenador = *(paradas + j);
                *(paradas + j) = *(paradas + j + 1);
                *(paradas + j + 1) = ordenador;
            }
        }
    }
    for (int i = 0; i < numparadas; ++i) {
        if (i == 0) {
            posibilidades = saltosPosibles(paradas[i] + 1, numsaltos, saltos);
        }
        else {
            posibilidades *= saltosPosibles(paradas[i] - paradas[i - 1], numsaltos, saltos);
        }
     veces = saltosPosibles(numescalones - paradas[numparadas - 1] + 1, numsaltos, saltos);
    }
    cout << "El numero total de posibilidades para subir la escalera es : " << posibilidades *veces << "\n";
}