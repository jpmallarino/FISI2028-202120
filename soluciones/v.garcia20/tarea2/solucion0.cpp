// Valentina Garcia Morales -201912546
// Tarea 2 

#include <iostream>
#include<Eigen/Dense>
#include<fstream>
#include <vector>

using namespace std;
using namespace Eigen;

//Parte 1: Primero necesitamos que guarde, abra y lea el archivo csv ; esta función esta basada en un tutorial.

void guardarMatriz(string nombreArchivo, MatrixXd  mimatriz)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(nombreArchivo);

    if (file.is_open())
    {
        file << mimatriz.format(CSVFormat);
        file.close();
    }

}
// En esta función, la idea es poder abrir el archivo en el que está la matriz 

MatrixXd abrirArchivo(string cualArchivo)
{
    ifstream matrizDatos(cualArchivo);

    string matricesFila, entrada;

    vector<double> valoresEntrada;

    int numeroFila = 0;


    while (getline(matrizDatos, matricesFila))
    {
        stringstream matrixRowStringStream(matricesFila);

        while (getline(matrixRowStringStream, entrada, ','))
        {
            valoresEntrada.push_back(stod(entrada));
        }
        numeroFila++;
    }

    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(valoresEntrada.data(), numeroFila, valoresEntrada.size() / numeroFila);

}
void imprimirMat(MatrixXd mimatriz, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j < m; j++)
        {
            cout << mimatriz(i, j) << " ";

        }
        guardarMatriz("Matriz Inversa de Gauss", mimatriz.inverse());
        cout << "\n";
    }

    return;
}


// Ahora, creamos la función para calcular la inversa con metodo gauss jordan.

void gaussj(MatrixXd mimatriz)
{
    int filasi = mimatriz.rows(), columnasi = mimatriz.cols();
    MatrixXd midentidad = MatrixXd::Identity(filasi, columnasi);

    MatrixXd matumentada(mimatriz.rows(), mimatriz.cols() + midentidad.cols());

    matumentada << mimatriz, midentidad;
    matumentada.row(0).swap(matumentada.row(filasi - 1));

    // Forma reduccion a la diagonal

    float mtemp;
    for (int i = 0; i < filasi; i++)
    {

        for (int j = 0; j < columnasi; j++)
        {

            if (j != i)
            {

                mtemp = matumentada(j, i) / matumentada(i, i);

                for (int k = 0; k < 2 * filasi; k++)
                {

                    matumentada(j, k) = matumentada(j, k) - matumentada(i, k) * mtemp;
                }
            }
        }
    }
    float temp2;
    MatrixXd final;



    for (int i = 0; i < filasi; i++)
    {

        temp2 = matumentada(i, i);

        for (int j = 0; j < filasi * filasi; j++)
        {

            matumentada(i, j) = matumentada(i, j) / temp2;

        }
    }
    imprimirMat(matumentada, filasi, filasi * 2);
}

//Ahora creamos el método para cofactores
int cofactores(MatrixXd mimatriz)
{
    MatrixXd matrizmini;
    int filasm = mimatriz.rows(), columnasm = mimatriz.cols(), ifilas, jcolumnas;
    int x = 0;
    int y = 0;

    for (ifilas = 0; ifilas < filasm * columnasm ; ifilas++)
    {
        for (jcolumnas = 0; jcolumnas < filasm*columnasm; jcolumnas++)
        {
            if (ifilas != filasm && jcolumnas != columnasm)
            {
                matrizmini(x, y) = mimatriz(ifilas, jcolumnas);
                y++;

                if (y >= filasm*columnasm - 1)
                {
                    y = 0; x++;


                }
            }
        }
    }

    return pow(-1.0, filasm + columnasm) * matrizmini.determinant();
}

int det(MatrixXd mimatriz)
{
    int inicial = 0;

    if (mimatriz.rows() == 1)
    {
        return mimatriz(0, 0);
    }
    // Guardo los cofactores 

    MatrixXd cofactor(mimatriz.rows(), mimatriz.rows());

    int signo = 1;

    
    
    for (int primerafila = 0; primerafila < mimatriz.rows(); ++primerafila)
    {

        cofactores(mimatriz);
        inicial += -signo * mimatriz(0, primerafila) * det(cofactor);
        signo = -signo;



    }

    return inicial;
}
void cofactinversa(MatrixXd mimatriz)
{
    int determinante = det(mimatriz);

    MatrixXd lafinal;

    for (int i = 0; i < mimatriz.rows(); i++)
    {
        for (int j = 0; j < mimatriz.rows(); j++)
        {
            lafinal = mimatriz.adjoint();
            lafinal = lafinal / determinante;
        }
    }
    cout << lafinal;
}
int main()
{
    MatrixXd prueba;
    prueba = abrirArchivo("CualArchivo");

    cout << "Su matriz es:" << "\n";
    cout << "\n\n" << prueba << "\n\n";

    MatrixXd gaussj;
    cout << "\n" "Matriz con metodo Gauss Jordan" << endl;
    cout << "\n";
    gaussj(prueba);

    cout << " La matriz inversa con Eigen:" << endl;
    cout << "\n";
    cout << prueba.inverse();
    cout << "\n";

    cofactinversa(prueba);
    guardarMatriz("Eigen Inversa", prueba.inverse());



}
