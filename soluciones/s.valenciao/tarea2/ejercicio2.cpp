#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#define MATRIZ "matriz.csv"

using namespace std;

float determiante(vector<vector<float>> v);

vector<vector<float>> leerArchivo(){
    vector<vector<float>> m;
    ifstream archivo(MATRIZ);
    string linea;
    char d = ',';
    int fila = 0;
    while (getline(archivo, linea)){
        m.emplace_back();
        stringstream stream(linea);
        string dato;
        while (getline(stream, dato, d)){
            m.at(fila).push_back(stof(dato));
//            cout << dato << " ";
        }
        fila++;
    }
    archivo.close();
    return m;
}

void guardarMatrizArchivo(vector<vector<float>> &v, string nombre){
    ofstream archivo(nombre, ofstream::out);
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
            if(j!=0){
                archivo << ',';
            }
            archivo << v.at(i).at(j);
        }
        archivo << '\n';
    }
    archivo.close();
}

void imprimirMatriz(){

}

void sumarFilas(vector<vector<float>> &v, int fila1, int fila2, float constante){
    for (int i = 0; i < v.size(); ++i) {
        v.at(fila1).at(i) += v.at(fila2).at(i) * constante;
    }
}

void cambioFila(vector<vector<float>> &v, int fila1, int fila2){
    v.at(fila1).swap(v.at(fila2));
//    return v;
}

void multiplicacionFila(vector<vector<float>> &v, int fila, float constante){
    for (float & i : v.at(fila)) {
        i = i * constante;
    }
}

float cofactor(vector<vector<float>> v, int fila, int columna){
    vector<vector<float>> s;
    int f = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (i != fila){
            s.emplace_back();
        }
        for (int j = 0; j < v.size(); ++j) {
            if (i != fila && j != columna){
                s.at(f).push_back(v.at(i).at(j));
            }
        }
        if (i != fila){
            f++;
        }
    }
    return pow(-1, fila + columna) * determiante(s);
}

float determiante(vector<vector<float>> v){
    float determiante = 0;
    double a;
    if (v.size() == 1){
        return v.at(0).at(0);
    }
    if (v.size() == v.at(0).size()){
        for (int i = 0; i < v.size(); ++i) {
            determiante += v.at(0).at(i) * cofactor(v, 0, i);
        }
    }
    return determiante;
}

vector<vector<float>> transpuesta(vector<vector<float>> v){
    vector<vector<float>> t;
    for (int i = 0; i < v.size(); ++i) {
        t.emplace_back();
        for (int j = 0; j < v.size(); ++j) {
            t.at(i).push_back(v.at(j).at(i));
        }
    }
    return t;
}

vector<vector<float>> adjunta(vector<vector<float>> v){
    vector<vector<float>> ad;
    for (int i = 0; i < v.size(); ++i) {
        ad.emplace_back();
        for (int j = 0; j < v.size(); ++j) {
            ad.at(i).push_back(cofactor(v, i, j));
//            if ((i+j)%2 == 1){
//                ad.at(i).at(j) *= -1;
//            }
        }
    }
    return ad;
}

int main(){
    float c;
    vector<vector<float>> m = leerArchivo();
    vector<vector<float>> mC = m;
    vector<vector<float>> inGJ = {};
    vector<vector<float>> inC;
    for (int i = 0; i < m.size(); ++i) {
        inGJ.emplace_back();
        for (int j = 0; j < m.size(); ++j) {
            if (i==j){
                inGJ.at(i).push_back(1);
            } else{
                inGJ.at(i).push_back(0);
            }
        }
    }
    inC = inGJ;


    if (m.size() == m.at(0).size()){
        for (int i = 0; i < m.size(); ++i) {
            if (m.at(i).at(i) == 0){
                for (int j = 0; j < m.size(); ++j) {
                    if (m.at(j).at(i) > 0) {
                        cambioFila(m, i, j);
                        cambioFila(inGJ, i, j);
                        break;
                    }
                }
            }
            c = 1/m.at(i).at(i);
            multiplicacionFila(m, i, c);
            multiplicacionFila(inGJ, i, c);
            for (int j = 0; j < m.size(); ++j) {
                if (i != j){
                    c = -m.at(j).at(i);
                    sumarFilas(m, j, i, c);
                    sumarFilas(inGJ, j, i, c);
                }
            }
        }
    }
    guardarMatrizArchivo(inGJ, "gj.csv");

    float determinate = determiante(mC);
    inC = adjunta(transpuesta(mC));
    for (int i = 0; i < inC.size(); ++i) {
        for (int j = 0; j < inC.size(); ++j) {
            inC.at(i).at(j) /= determinate;
        }
    }

    guardarMatrizArchivo(inC, "cofactores.csv");
}
