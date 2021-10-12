#include <iostream>
#include <fstream>
#include <string>
#include <stdlib>
#include <stdio>
#include <eigen-3.4.0/Eigen/Dense>

using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;

//Declaracion de funciones
//Funcion cargar archivo de matriz
MatrixXd readMatrix(string documento);


//Funcion que da la matriz

typedef struct{
	double **datos;
	int row;
	int col;
}Matriz;

Matriz inicializa(int filas, int cols) {
	Matrix M;
	M.row = filas;
	M.col = columnas;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = 0.0;
		}
	}
	return M;
}




int main()
{
int m;
int n;

string Documento;
cout << "Introduzca el nombre del documento";
cin >> Documento;

cout << readMatrix(Documento) << endl;

}

#define MAXBUFSIZE  ((int) 15000)

MatrixXd readMatrix(string documento)
{
    int cols = 0, rows = 0;
    double buff[MAXBUFSIZE];

    // Read numbers from file into buffer.
    ifstream infile;
    infile.open(documento.c_str());
    while (!infile.eof())
    {
        string line;
        getline(infile, line);

        int temp_cols = 0;
        stringstream stream(line);
        while (!stream.eof())
            stream >> buff[cols * rows + temp_cols++];

        if (temp_cols == 0)
            continue;

        if (cols == 0)
            cols = temp_cols;

        rows++;
    }

    infile.close();

    rows--;

    // Populate matrix with numbers.
    MatrixXd result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i, j) = buff[cols * i + j];

    return result;
};

//  MatrixXd m(2,2);
//  m(0,0) = 3;
//  m(1,0) = 2.5;
//  m(0,1) = -1;
//  m(1,1) = m(1,0) + m(0,1);
//  std::cout << m << std::endl;

  



//Punto a) Reduccion Gauss Jordan


