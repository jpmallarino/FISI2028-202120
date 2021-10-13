#include <iostream>
#include<Eigen/Dense>
#include<fstream>
#include <vector>
#include <cmath>
using namespace std;
using namespace Eigen;

void saveData(string fileName, MatrixXd  matrix)
{
    //https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

    ofstream file(fileName);
    if (file.is_open())
    {
        file << matrix.format(CSVFormat);
        file.close();
    }
}
MatrixXd openData(string fileToOpen)
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
MatrixXd gaussJordan(MatrixXd mx) {
    int filas = mx.rows();
    int columnas = mx.cols();
    MatrixXd identidad = MatrixXd::Identity(filas, columnas);
    MatrixXd aumentada(mx.rows(), mx.cols() + identidad.cols());
    aumentada << mx, identidad;
    aumentada.row(0).swap(aumentada.row(filas - 1));
    MatrixXd final(filas, columnas);
    float aux;
    for (int i = 0; i < filas; i++) {

        for (int j = 0; j < columnas; j++) {

            if (j != i) {

                aux = aumentada(j, i) / aumentada(i, i);
                for (int k = 0; k < 2 * filas; k++) {

                    aumentada(j, k) -= aumentada(i, k) * aux;
                }
            }
        }
    }
    float aux2;

    for (int i = 0; i < filas; i++) {

        aux2 = aumentada(i, i);
        for (int j = 0; j < 2 * filas; j++) {

            aumentada(i, j) = aumentada(i, j) / aux2;

        }
    }
    final = aumentada.block(0, filas, filas, filas);
    return final;
}

void getCofactor(int** A , int** temp , int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
           
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
int determinant(int**A, int n)
{
    int D = 0; 
    if (n == 1)
        return A[0][0];

    int** temp = new int* [n];
    for (int i = 0; i < n; i++) {
        temp[i] = new int[n];
    }

    int sign = 1;  
    for (int f = 0; f < n; f++)
    {
       
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        
        sign = -sign;
    }

    return D;
}
void adjoint(int** A, int** adj, int N)
{
   
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    
    int sign = 1;
    int** temp = new int* [N];
    for (int i = 0; i < N; i++) {
        temp[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            
            getCofactor(A, temp, i, j, N);

            
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}
MatrixXd inverse(int**A, float** inverse, int N)
{  
    MatrixXd mx(N, N);
    int det = determinant(A, N);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        
    }
    int** adj = new int* [N];
    for (int i = 0; i < N; i++) 
        adj[i] = new int[N]; 
    adjoint(A, adj,N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverse[i][j] = adj[i][j] / float(det);

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            mx(j, i) = inverse[j][i];
            
        }
    }
    return mx;

}
int main()
{
    MatrixXd matrix_test3;
    MatrixXd prueba(matrix_test3.rows(),matrix_test3.cols());
    //Insertar FileName
    matrix_test3 = openData("FileName");
    int fila = matrix_test3.rows();
    int columna = matrix_test3.cols();
    int** matrixn = new int* [fila];
    for (int i = 0; i < fila; i++) {
        matrixn[i] = new int[columna];
    }
    for (int i = 0; i < fila; i++)
        for (int j = 0; j < columna; j++)
            *(*(matrixn + i) + j) = matrix_test3(i, j);

    float** aux = new float* [fila];
    for (int i = 0; i < fila; i++) {
        aux[i] = new float[columna];
    }
    for (int i = 0; i < fila; i++)
        for (int j = 0; j < columna; j++)
            *(*(aux + i) + j) = matrix_test3(i, j);
    cout << "La matriz dada es:" << "\n";
    cout << matrix_test3 << "\n";
    cout << "La matriz usando el metodo de cofactores es:" << "\n";
    cout << inverse(matrixn, aux, fila) << "\n";
    saveData("InversaCofactores", inverse(matrixn, aux, fila));
    cout << "La matriz usando el metodo Gauss-Jordan es:" << "\n";
    cout <<gaussJordan(matrix_test3);
    saveData("inversaGaussJordan", gaussJordan(matrix_test3));
    cout << "La inversa usando Eigen es:" << "\n";
    cout << matrix_test3.inverse()<<"\n";
    saveData("inversaEigen", matrix_test3.inverse());
}

/*Referencias:
* https://www.geeksforgeeks.org/adjoint-inverse-matrix/
* https://eigen.tuxfamily.org/dox/index.html
* https://aleksandarhaber.com/eigen-matrix-library-c-tutorial-saving-and-loading-data-in-from-a-csv-file/
* https://aleksandarhaber.com/starting-with-eigen-c-matrix-library/
* https://www.geeksforgeeks.org/finding-inverse-of-a-matrix-using-gauss-jordan-method/
*/