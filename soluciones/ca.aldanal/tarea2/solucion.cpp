#include <iostream>
#include<Eigen/Dense>
#include<fstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;
int fila, columna, orden;
float **nueva_matriz,  **auxiliar_matriz;
MatrixXd matriz_archivo;


MatrixXd Abrir_archivo(string);
void Imprimir_matriz(MatrixXd, int, int);
void Gauss_Jordan(MatrixXd);
int Menor(float**, float**, int, int, int);
double Determinante_valor(float**, int);
void Matriz_inversa(float**, int, float**);
void Guardar_archivo(string, MatrixXd);

int main()
{
    matriz_archivo = Abrir_archivo("matriz.csv");
 
    fila = matriz_archivo.rows();
    columna = matriz_archivo.cols();
    orden = matriz_archivo.rows() * matriz_archivo.cols();

    nueva_matriz = new float* [fila];
    for (int i = 0; i < fila; i++) {
        nueva_matriz[i] = new float[columna];
    }
    auxiliar_matriz = new float* [fila];
    for (int i = 0; i < fila; i++) {
        auxiliar_matriz[i] = new float[columna];
    }

    for (int i = 0; i < fila; i++)
        for (int j = 0; j < columna; j++)
            *(*(nueva_matriz+i)+j) = matriz_archivo(i,j);

    for (int i = 0; i < fila; i++)
        for (int j = 0; j < columna; j++)
            *(*(auxiliar_matriz + i) + j) = matriz_archivo(i, j);

    cout << "\n";
    cout << "Inversa utilizando Gauss-Jordan:" << endl;
    cout << "\n";
    Gauss_Jordan(matriz_archivo);
    cout << "\n";
    cout << "\n";
    cout << "Inversa utilizando cofactores:" << endl;
    cout << "\n";
    Matriz_inversa(nueva_matriz, fila, auxiliar_matriz);
    cout << "\n";
    cout << "\n";
    cout << "Inversa utilizando Eigen:" << endl;
    cout << "\n";
    cout << matriz_archivo.inverse();
    cout << "\n";

    Guardar_archivo("InversaEigen", matriz_archivo.inverse());
  

    system("pause>nul");
    return 0;
}

MatrixXd Abrir_archivo(string fileToOpen)
{
    vector<double> matrixEntries;

    ifstream matrixDataFile(fileToOpen);

    string matrixRowString;

    string matrixEntry;

    int matrixRowNumber = 0;

    while (getline(matrixDataFile, matrixRowString))
    {
        stringstream matrixRowStringStream(matrixRowString); 

        while (getline(matrixRowStringStream, matrixEntry, ',')) 
        {
            matrixEntries.push_back(stod(matrixEntry));  
        }
        matrixRowNumber++;
    }

    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);

}
void Imprimir_matriz(MatrixXd a, int n, int m)
{
    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = n; j < m; j++) {
            cout << a(i, j) << " ";     
        }
        Guardar_archivo("InversaGauss", matriz_archivo.inverse());
        cout << "\n";
    }
    
    return;
}

void Gauss_Jordan(MatrixXd matriz) {

    MatrixXd identidad = MatrixXd::Identity(fila, columna);
    MatrixXd aumentada(matriz.rows(), matriz.cols() + identidad.cols());
    aumentada << matriz, identidad;
    aumentada.row(0).swap(aumentada.row(fila - 1));

    float aux;
    for (int i = 0; i < fila; i++) {

        for (int j = 0; j < columna; j++) {

            if (j != i) {

                aux = aumentada(j, i) / aumentada(i, i);
                for (int k = 0; k < 2 * fila; k++) {

                    aumentada(j, k) -= aumentada(i, k) * aux;
                }
            }
        }
    }
    float aux2;
    MatrixXd final;
    for (int i = 0; i < fila; i++) {

        aux2 = aumentada(i, i);
        for (int j = 0; j < 2 * fila; j++) {

            aumentada(i, j) = aumentada(i, j) / aux2;

        }
    }

    Imprimir_matriz(aumentada, fila, 2 * fila);
}

int Menor(float** src, float** dest, int fila, int columna, int orden)
{

    int Num_columnas = 0, Num_filas = 0;

    for (int i = 0; i < orden; i++)
    {
        if (i != fila)
        {
            Num_columnas = 0;
            for (int j = 0; j < orden; j++)
            {

                if (j != columna)
                {
                    dest[Num_filas][Num_columnas] = src[i][j];
                    Num_columnas++;
                }
            }
            Num_filas++;
        }
    }

    return 1;
}

double Determinante_valor(float** nueva_matriz, int orden)
{

    if (orden == 1)
        return nueva_matriz[0][0];


    float det = 0;


    float** min;
    min = new float* [orden - 1];
    for (int i = 0; i < orden - 1; i++)
        min[i] = new float[orden - 1];

    for (int i = 0; i < orden; i++)
    {
        Menor(nueva_matriz, min, 0, i, orden);

        det += (i % 2 == 1 ? -1.0 : 1.0) * nueva_matriz[0][i] * Determinante_valor(min, orden - 1);

    }

    for (int i = 0; i < orden - 1; i++)
        delete[] min[i];
    delete[] min;

    return det;
}

void Matriz_inversa(float** A, int orden, float** Y)
{
    MatrixXd K;

    double det = 1.0 / Determinante_valor(A, orden);

    float* Aux = new float[(orden - 1) * (orden - 1)];
    float** min = new float* [orden - 1];
    for (int i = 0; i < orden - 1; i++)
        min[i] = Aux + (i * (orden - 1));

    for (int j = 0; j < orden; j++)
    {
        for (int i = 0; i < orden; i++)
        {
 
            Menor(A, min, j, i, orden);
            Y[i][j] = det * Determinante_valor(min, orden - 1);
            if ((i + j) % 2 == 1)
                Y[i][j] = -Y[i][j];
        }
       
    }
    cout << "\n";
    for (int j = 0; j < fila; j++) {
        for (int i = 0; i < columna; i++) {
            cout << Y[j][i] << " ";
        }
        cout << "\n";
    }
    Guardar_archivo("InversaCofactores", matriz_archivo.inverse());

    delete[] Aux;
    delete[] min;
}

void Guardar_archivo(string fileName, MatrixXd  matriz)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(fileName);
    if (file.is_open())
    {
        file << matriz.format(CSVFormat);
        file.close();
    }
}
