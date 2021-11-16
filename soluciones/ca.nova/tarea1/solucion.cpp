//Tarea 1 Metodos Computacionales
//Cristian Andres Nova Arevalo
//201913525


#include<iostream>
#include<stdlib.h>

using namespace std;


int caminos(int n, int numSteps, int steps[]) {
    int cont = 0;
    if ( n==1 || n==0) {
        return n;
    }
    else if (n < 0) {
        return 0;
    }
    else {
        for (int i = 0; i < numSteps; i++) {
            cont += caminos(n - steps[i], numSteps, steps);
        }
        return cont;
    }
}

void ordenar(int numParadas, int paradas[]) {
    int x;
    for (int i = 0; i < numParadas; i++) {
        for (int j = 0; j < numParadas - 1; j++) {
            if (*(paradas + j) > *(paradas + j + 1)) {
                x = *(paradas + j);
                *(paradas + j) = *(paradas + j + 1);
                *(paradas + j + 1) = x;
            }
        }
    }

}

int main() {
    
    int numSteps;
    int stair;
    int numParadas;
    int cont;
    int formsPosibles;
    int posibilidades;
    int cantidad;
    int* paradas;
    int* steps;
        
    cout << "Escriba la cantidad de escalones que va a subir ";
    cin >> stair;
    cout << "Escriba la cantidad de diferentes pasos que puede dar ";
    cin >> numSteps;
    
    steps = new int[numSteps];

    for (int i = 0; i < numSteps; i++) {
        cout << "Escriba los pasos uno por uno ";
        cin >> steps[i];
    }
    cout << "Escriba el numero de paradas de descanso que hara ";
    cin >> numParadas;
    paradas = new int[numParadas];

    for (int i = 0; i < numParadas; i++) {
        cout << "Escriba los escalones en donde hara las paradas ";
        cin >> paradas[i];
    }

    ordenar(numParadas, paradas);

    if (numParadas <= 0) {
        formsPosibles = 1;
        cantidad = caminos(stair, numSteps, steps);
    }
    else {
        posibilidades = 1;
        cont = 0;
        for (int i = 0; i < numParadas; i++) {
            if (i != 0) {
                
                cont = caminos(paradas[i] - paradas[i - 1] + 1, numSteps, steps);
                posibilidades *= cont;
                
            }
            else {
                
                formsPosibles = caminos(paradas[i] + 1, numSteps, steps);
            }
        }
        cantidad = caminos(stair - paradas[numParadas - 1] + 1, numSteps, steps);
    }

    if (numParadas == 0)
    {
        cantidad -= 1;
    }
    if (numParadas > 1) {
        formsPosibles *= posibilidades;

    }
    cout << "El numero de posibilidades para subir la escalera es de " << formsPosibles * cantidad << "\n";
}