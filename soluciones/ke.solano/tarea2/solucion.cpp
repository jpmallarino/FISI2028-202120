#include <iostream>
#include<Eigen/Dense>
#include<fstream>
#include<sstream>
#include<vector>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;
using namespace Eigen;

COORD coord = {0,0};

//Función para que se proyecte mi matriz donde yo quiera

void darxy(int x, int y) {
    
    coord.X= x;
    coord.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Función para Abrir la matriz en formato Eigen

MatrixXd openData(string fileToOpen)
{
    // Esta función fue tomada de: 
    // https://aleksandarhaber.com/eigen-matrix-library-c-tutorial-saving-and-loading-data-in-from-a-csv-file/

    vector<double> matrixEntries;

    ifstream matrixDataFile(fileToOpen);

    string matrixRowString;

    string matrixEntry;

    int matrixRowNumber = 0;

    while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString
    {
        stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.

        while (getline(matrixRowStringStream, matrixEntry, ' ')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
        {
            matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
        }
        matrixRowNumber++; //update the column numbers
    }
    // here we convet the vector variable into the matrix and return the resulting object, 
    // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / (matrixRowNumber));

}

int main()
{
    short int i, j, k, n;
    cout << "Ingrese el número de las columnas de la matrix: ";
    cin >> n;

    MatrixXd A;
    A = openData("matrix.txt");
    
    
    float I[n][n], aux, pivot;

    // load the matrix from the file:

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            darxy(j * 5, i + 3);
            cout << A.row(i).col(j);
        }
    }

    //Identidad
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            darxy(30 + j * 5 , i + 3);
            I[i][j] = 0.0;
            if (i == j) {
                I[i][j] = 1.0;
            }
            cout << I[i][j];
        }
        cout << "\n";
        cout << "\n";
    }
    //Gauss
    for (i = 0; i < n; i++) {

            pivot = A.row(i).col(i).value();

            for (k = 0; k < n; k++) {
                A.row(i).col(k).sum()/ pivot;
                I[i][k] = (I[i][k]) * (1 / pivot);
            }
            for (j = 0; j < n; j++) {
                if (i != j) {
                    aux = A.row(j).col(i).sum();
                    for ( k = 0; k < n; k++) {
                        A.row(j).col(i).sum() - aux * A.row(j).col(i).value();
                        I[j][k] = I[j][k] - ((aux)*I[i][k]);
                    }

                }
            }
    }

    cout << "Inversa por Gauss Jordan: \n " << endl;

    for ( i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {

            darxy(j * 10, i + 10);
            cout << I[i][j] << endl;
        }
        
    }
    cout << "\n";
    cout << "\n";

    cout << "Inversa por funcion Eigen: \n " << endl;

    cout << A.inverse();

    cout << "Det: \n " << endl;

    cout<<A.determinant()<<endl;

    return 0;
}
