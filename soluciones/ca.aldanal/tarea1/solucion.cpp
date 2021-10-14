#include<iostream>
#include<stdlib.h>

using namespace std;
int contador, numero_saltos, numero_escalones, numero_paradas, posibilidades, aux, posibles, * paradas, * pasos;
void ordenar_arreglo(int, int*);
void pedir_escalones();
void pedir_saltos();
void pedir_paradas();
int formasPosiblesSaltos(int);


int main() {
   
    pedir_escalones();
    pedir_saltos();
    pedir_paradas();
    ordenar_arreglo(numero_paradas, paradas);

    if (numero_paradas == 0) {
        posibilidades = 1;
        posibles = formasPosiblesSaltos(numero_escalones+1);
    }
    else {
        aux = 1;
        contador = 0;
        for (int i = 0; i < numero_paradas; ++i) {
            if (i == 0) {
                posibilidades = formasPosiblesSaltos(paradas[i] + 1);
            }

            else {
                contador = formasPosiblesSaltos(paradas[i] - paradas[i - 1] + 1);
                aux = aux * contador;
            }
        }
        posibles = formasPosiblesSaltos(numero_escalones - paradas[numero_paradas - 1] + 1);
    }

    if (numero_paradas > 1) {
        posibilidades = posibilidades * aux;

    }
    cout << "\nEl numero total de posibilidades para subir la escalera es: " << posibilidades * posibles << "\n";
    system("pause>0");
}

void pedir_escalones() {
    cout << "Ingrese el numero de escalones que tiene la escalera: ";
    cin >> numero_escalones;
}

void pedir_saltos(){
    cout << "Ingrese el numero de posibles saltos: ";
    cin >> numero_saltos;

    if (numero_saltos <= 0) {
        cout << "Ingrese saltos posibles, las gradas no se subiran solas." << endl;
        exit(-1);
    }

    if (numero_saltos > numero_escalones) {
        cout << "No pueden haber mas saltos que escalones. Intente nuevamente." << endl;
        exit(-1);
    }
    pasos = new int[numero_saltos];

    for (int i = 0; i < numero_saltos; ++i) {
        cout << "Ingrese el numero de escalones que puede saltar en la forma de salto " << i + 1 << ": ";
        cin >> pasos[i];
    }

    for (int i = 0; i < numero_saltos; ++i) {
        if (pasos[i] > numero_escalones or pasos[i] <= 0) {
            cout << "\nSalto imposible. Intente nuevamente." << endl;
            exit(-1);
        }
    }

    for (int i = 0; i < 1; i++) {
        for (int j = 1; j < numero_saltos; ++j) {
            if (pasos[j] == pasos[i]) {
                cout << "\nLos tipos de salto no deben repetirse. Intente nuevamente." << endl;
                exit(-1);
            }
        }
    }
}

void pedir_paradas(){
    cout << "Ingrese el numero de paradas que desea realizar: ";
    cin >> numero_paradas;
    if (numero_paradas < 0) {
        cout << "Numero de paradas invalido." << endl;
        exit(-1);
    }

    paradas = new int[numero_paradas];

    for (int i = 0; i < numero_paradas; ++i) {
        cout << "Ingrese el escalon en donde desea realizar la parada " << i + 1 << ": ";
        cin >> paradas[i];
    }

    if (numero_paradas > numero_escalones) {
        cout << "No hay suficientes escaleras para descansar." << endl;
        exit(-1);
    }

    for (int i = 0; i < numero_paradas; ++i) {
        if (paradas[i] >= numero_escalones or paradas[i] <= 0) {
            cout << "\nSu escalon de descaso no existe o corresponde a la cima o base de la escalera. Intente nuevamente." << endl;
            exit(-1);
        }
    }
    for (int i = 0; i < 1; i++) {
        for (int j = 1; j < numero_paradas; ++j) {
            if (paradas[j] == paradas[i]) {
                cout << "\nLos sitios de parada no pueden repetirse. Intente nuevamente." << endl;
                exit(-1);
            }
        }
    }
}

void ordenar_arreglo(int numeroParadas, int* paradas) {
    int aux;
    for (int i = 0; i < numeroParadas; i++) {
        for (int j = 0; j < numeroParadas - 1; j++) {
            if (*(paradas + j) > *(paradas + j + 1)) {
                aux = *(paradas + j);
                *(paradas + j) = *(paradas + j + 1);
                *(paradas + j + 1) = aux;
            }
        }
    }

}

int formasPosiblesSaltos(int n) {
    int numero = 0;
    if (n == 0 || n == 1) {
        return n;
    }
    else if (n < 0) {
        return 0;
    }
    else {
        for (int i = 0; i < numero_saltos; ++i) {
            numero += formasPosiblesSaltos(n - pasos[i]);
        }
        return numero;
    }
}