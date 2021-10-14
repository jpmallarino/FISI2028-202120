#include <iostream>
#include<Eigen/Dense>
#include<fstream>
#include <vector>

using namespace std;
using namespace Eigen;

//Prototipo de Funciones
void crearArchivo(string, MatrixXd);
MatrixXd leerArchivo(string);
MatrixXd gaussInversa(MatrixXd);
MatrixXd cfactInversa(MatrixXd);


//Función principal
int main() {

    MatrixXd m = leerArchivo("D:\\Documents\\matriz.txt");

    MatrixXd inversaXGauss = gaussInversa(m);
    crearArchivo("InversaXGauss.txt", inversaXGauss);

    MatrixXd inversaXCofact = cfactInversa(m);
    crearArchivo("InversaXCofact.txt", inversaXCofact);

    MatrixXd inversaXEigen = m.inverse();
    crearArchivo("InversaXEigen.txt", inversaXEigen);
    
}

//Me calcula la inversa por el metodo de Gauss Jordan
MatrixXd gaussInversa(MatrixXd original) {

    int n = original.rows(); 
    int aux, pivot;
    MatrixXd identidad(n, n);

    //Hacemos la matriz identidad
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                identidad(i, j) = 1;
            }
            else {
                identidad(i, j) = 0;
            }
        }
    }

    //Reducción
    for (int i = 0; i < n; i++) {
        pivot = original(i, i);
        for (int k = 0; k < n; k++) {
            original(i, k) /= pivot;
            identidad(i, k) /= pivot; 
        }
        for (int j = 0; j < n; j++) {
            if (i != j) {
                aux = original(j, i);
                for (int k = 0; k < n; k++) {
                    original(j, k) -= aux * original(i, k);
                    identidad(j, k) -= aux * identidad(i, k);
                }
            }
        }
    }
    return identidad;
}

//Me calcula la inversa por el metodo de Cofactores
MatrixXd cfactInversa(MatrixXd original) {

    int det = 0;
    int n = original.rows();
    MatrixXd inversa(n, n);

    for (int i = 0; i < n; i++) {
        det = det + (original(0, i) * (original(1, (i + 1) % n) * original(2, (i + 2) % n) - original(1, (i + 2) % n) * original(2, (i + 1) % n)));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversa(i, j) = ((original((j + 1) % n, (i + 1) % n) * original((j + 2) % n, (i + 2) % n)) - (original((j + 1) % n, (i + 2) % n) * original((j + 2) % n, (i + 1) % n))) / det;
        }
     }
    return inversa;
}

//Me lee el archivo csv con la matriz original
MatrixXd leerArchivo(string archivo) {

    vector<double> entradas;
    ifstream archivoMatriz(archivo);
    string Fila, entry;
    int numerofila = 0;

    while (getline(archivoMatriz, Fila)) {
        stringstream ssfila(Fila);
        while (getline(ssfila, entry, ','))
        {
            entradas.push_back(stod(entry));
        }
        numerofila++;
    }
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(entradas.data(), numerofila, entradas.size() / numerofila);
}

//Me guarda el archivo con la matriz inversa
void crearArchivo(string archivo, MatrixXd  matriz) {
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(archivo);
    if (file.is_open())
    {
        file << matriz.format(CSVFormat);
        file.close();
    }
}

