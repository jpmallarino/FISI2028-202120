#include <iostream>
#include<Eigen/Dense>
#include<fstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;

//Prototipo 
void Guardar(string, MatrixXd);
MatrixXd Leer(string);
MatrixXd Inversa_Gauss(MatrixXd);
void Cofactores(int*, int*, int, int, int);
int Determinante(int**, int);
void Matriz_Adjunta(int*, int*, int);
MatrixXd Inversa_Cofactores(int*, float*, int);

void Guardar(string nombre, MatrixXd  matriz)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");
    ofstream file(nombre);

    if (file.is_open())
    {
        file << matriz.format(CSVFormat);
        file.close();
    }
}
MatrixXd Leer(string archivo)
{

    vector<double> entradasMatriz;
    ifstream archivoMatriz(archivo);
    string filaMatriz, entrada;

    int numFila = 0;


    while (getline(archivoMatriz, filaMatriz))
    {
        stringstream secuencia(filaMatriz);

        while (getline(secuencia, entrada, ','))
        {
            entradasMatriz.push_back(stod(entrada));
        }
        numFila++;
    }

    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(entradasMatriz.data(), numFila, entradasMatriz.size() / numFila);

}
MatrixXd Inversa_Gauss(MatrixXd mx) {
    int n = mx.rows();
    int m = mx.cols();
    MatrixXd inversa(n, m);

    MatrixXd identidad = MatrixXd::Identity(n, m);
    MatrixXd aumentada(mx.rows(), mx.cols() + identidad.cols());
    aumentada << mx, identidad;
    aumentada.row(0).swap(aumentada.row(n - 1));



    float indice_a;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {

            if (j != i) {

                indice_a = aumentada(j, i) / aumentada(i, i);
                for (int k = 0; k < 2 * n; k++) {

                    aumentada(j, k) -= aumentada(i, k) * indice_a;
                }
            }
        }
    }

    float indice_b;

    for (int i = 0; i < n; i++) {

        indice_b = aumentada(i, i);
        for (int j = 0; j < 2 * n; j++) {

            aumentada(i, j) = aumentada(i, j) / indice_b;

        }
    }

    inversa = aumentada.block(0, n, n, n);

    return inversa;
}

void Cofactores(int** src, int** temp, int n, int m, int grado)
{
    int numFilas = 0, numColumas = 0;

    for (int f = 0; f < grado; f++)
    {
        for (int c = 0; c < grado; c++)
        {
            if (f != n && c != m)
            {
                temp[numFilas][numColumas++] = src[f][c];
                if (numColumas == grado - 1)
                {
                    numColumas = 0;
                    numFilas++;
                }
            }
        }
    }
}
int Determinante(int** M, int grado)
{

    if (grado == 1)
        return M[0][0];

    int determinante = 0;
    int** t = new int* [grado];

    for (int i = 0; i < grado; i++) {
        t[i] = new int[grado];
    }

    int x = 1;

    for (int f = 0; f < grado; f++)
    {

        Cofactores(M, t, 0, f, grado);
        determinante += x * M[0][f] * Determinante(t, grado - 1);


        x = -x;
    }

    return determinante;
}
void Matriz_Adjunta(int** Ma, int** adjunta, int grado)
{

    if (grado == 1)
    {
        adjunta[0][0] = 1;
        return;
    }

    int x = 1;
    int** t = new int* [grado];

    for (int i = 0; i < grado; i++) {
        t[i] = new int[grado];
    }

    for (int i = 0; i < grado; i++)
    {
        for (int j = 0; j < grado; j++)
        {
            Cofactores(Ma, t, i, j, grado);
            x = ((i + j) % 2 == 0) ? 1 : -1;
            adjunta[j][i] = (x) * (Determinante(t, grado - 1));
        }
    }
}

MatrixXd Inversa_Cofactores(int** M, float** I, int fila)
{
    MatrixXd inversa(fila, fila);
    int d = Determinante(M, fila);
    int** a = new int* [fila];

    for (int i = 0; i < fila; i++)
        a[i] = new int[fila];

    Matriz_Adjunta(M, a, fila);

    for (int i = 0; i < fila; i++)
        for (int j = 0; j < fila; j++)
            I[i][j] = a[i][j] / float(d);

    for (int j = 0; j < fila; j++)
    {
        for (int i = 0; i < fila; i++)
        {
            inversa(j, i) = I[j][i];
        }
    }
    return inversa;

}

int main()
{
    MatrixXd matrizOriginal;
    MatrixXd prueba(matrizOriginal.rows(), matrizOriginal.cols());

    matrizOriginal = Leer("archivo2.csv");

    int n = matrizOriginal.rows();
    int m = matrizOriginal.cols();
    int** x = new int* [n];
    float** y = new float* [n];

    for (int i = 0; i < n; i++) {
        x[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(*(x + i) + j) = matrizOriginal(i, j);

    
    for (int i = 0; i < n; i++) {
        y[i] = new float[m];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(*(y + i) + j) = matrizOriginal(i, j);

    cout << "La matriz a invertir es:";
    cout << "\n";
    cout << matrizOriginal;
    cout << "\n";
    cout << "La inversa de la matriz usando el metodo de eliminacion por Gauss-Jordan es:";
    cout << "\n";
    cout << Inversa_Gauss(matrizOriginal);
    cout << "\n";
    Guardar("inversaGaussJordan", Inversa_Gauss(matrizOriginal));
    cout << "La inversa de la matriz usando cofactores es:";
    cout << "\n";
    cout << Inversa_Cofactores(x, y, n);
    cout << "\n";
    Guardar("InversaCofactores", Inversa_Cofactores(x, y, n));
    cout << "La inversa de la matriz usando Eigen es:";
    cout << "\n";
    cout << matrizOriginal.inverse();
    cout << "\n";
    Guardar("inversaEigen", matrizOriginal.inverse());
}
