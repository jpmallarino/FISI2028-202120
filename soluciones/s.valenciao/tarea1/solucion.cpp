#include <bits/stdc++.h>

using namespace std;

int formasPosibles(int n, int numeroPasos, int pasos[]){
    int numero = 0;
    if (n == 0 || n == 1) {
        return n;
    }else if (n<0) {
        return 0;
    }else {
        for (int i = 0; i < numeroPasos; ++i) {
            numero += formasPosibles(n - pasos[i], numeroPasos, pasos);
        }
        return numero;
    }
}

int main(){
    int numeroPasos, escalones, numeroParadas, cantidadFormasPosibles;
    cout << "digite la cantidad de escalones:";
    cin >> escalones;
    cout << "digite la cantidad de diferentes pasos:";
    cin >> numeroPasos;
    cout << "digite los pasos:";
    int pasos[numeroPasos];
    for (int i = 0; i < numeroPasos; ++i) {
        int paso;
        cin >> paso;
        pasos[i] = paso;
    }
    cout << "digite la cantidad de paradas de descanso:";
    cin >> numeroParadas;
    cout << "digite las paradas:";
    int paradas[numeroParadas];
    for (int i = 0; i < numeroParadas; ++i) {
        int parada;
        cin >> parada;
        paradas[i] = parada;
    }
    sort(paradas, paradas + numeroParadas);
    for (int i = 0; i < numeroParadas; ++i) {
        if(i == 0){
            cantidadFormasPosibles = formasPosibles(paradas[i]+1, numeroPasos, pasos);
        }else{
            cantidadFormasPosibles += formasPosibles(paradas[i]-paradas[i-1], numeroPasos, pasos);
        }
    }
    cout << "# total de posibilidades para subir la escalera: "<< cantidadFormasPosibles << "\n";
}