
#include <iostream>
#include <eigen-3.4.0/Eigen/Dense>
#include<fstream>
#include<vector>

using namespace std;
using namespace Eigen;



// TAREA 2


// El codigo para la manipulacion de archivos fue modificado de la fuente dada por el curso
// -> https://aleksandarhaber.com/eigen-matrix-library-c-tutorial-saving-and-loading-data-in-from-a-csv-file/


//Funcion para guardar archivos
void saveData(string fileName, MatrixXd  matrix)
{
	const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

	ofstream file(fileName);
	if (file.is_open())
	{
		file << matrix.format(CSVFormat);
		file.close();
	}
}


//Funcion para abrir archivos
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



//------------------------------------------------------------------------------

//Funcion para obtener matriz identidad
MatrixXd identidad(int filas, int cols) {
	MatrixXd N;
	N.resize(filas, cols);
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < cols; j++) {
			N(i,j) = 0.0;
		}
		N(i,i) = 1.0;
	}
	return N;
}


//Funcion para cambiar filas

MatrixXd cambiarFilas(MatrixXd  N, int r1, int r2) {
	float aux;
	
	for (int i = 0; i < N.cols(); i++) {
		aux = N(r1,i);
		N(r1,i) = N(r2,i);
		N(r2,i) = aux;
	}

	return N;
}

//Funcion Multiplicar fila por constante

MatrixXd FilaXCte(MatrixXd M, int r, float c) {
	for (int i = 0; i < M.cols(); i++) {
		M(r,i)*= c;
	}

	return M;
}

//Funcion Sumar filas

MatrixXd sumarFilas(MatrixXd M, int r1, int r2, float c) {
	for (int i = 0; i < M.cols(); i++) {
		M(r1,i) += M(r2,i) * c;
	}

	return M;
}

//Gauss Jordan

MatrixXd gaussjordann(MatrixXd  M) {
	
	MatrixXd Inv = identidad(M.rows(), M.cols());
	if (M.rows() == M.cols()) {
		
		
		for (int i = 0; i < M.rows(); i++) {
			cout << Inv << "\n";
			
			if (M(i,i) == 0.0) {
				
				int r = 0;
				while (r < M.cols() && (M(i,r) == 0 || M(r,i) == 0)) {
					r++;
				}
				
				M = cambiarFilas(M,i,r);
			}
			system("pause");
			double c = 1.0 / M(i,i);
			M = FilaXCte(M, i, c);
			Inv = FilaXCte(Inv, i, c);
			for (int j = 0; j < M.rows(); j++) {
				if (i != j) {
					c = -M(j,i);
					M = sumarFilas(M, j, i, c);
					Inv = sumarFilas(Inv, j, i, c);
				}
			}
		}
	}else {
		printf("Error La matriz no cumple la regla de ser cuadrada \n");
		
	}
	return Inv;
}

//Cofactores

MatrixXd Cofactores(MatrixXd  M) {
	
	MatrixXd Inv = identidad(M.rows(), M.cols());
	if (M.rows() == M.cols()) {
		
		
		for (int i = 0; i < M.rows(); i++) {
			cout << Inv << "\n";
			system("pause");
			if (M(i,i) == 0) {
				int r = 0;
				while (r < M.cols() && (M(i,r) == 0 || M(r,i) == 0)) {
					r++;
				}
				
				M = cambiarFilas(M,i,r);
			}
			double c = 1.0 / M(i,i);
			M = FilaXCte(M, i, c);
			Inv = FilaXCte(Inv, i, c);
			for (int j = 0; j < M.rows(); j++) {
				if (i != j) {
					c = -M(j,i);
					M = sumarFilas(M, j, i, c);
					Inv = sumarFilas(Inv, j, i, c);
				}
			}
		}
	}else {
		printf("Error La matriz no cumple la regla de ser cuadrada \n");
		
	}
	return Inv;
}

//==========================================================================================
//============================================MAIN==========================================
//==========================================================================================
int main()
{	
	//OBTENER MATRIZ DE ARCHIVO DADO -------------------------------------------------------

	string Documento;
	cout << "Introduzca el nombre del documento CSV:  \n";
	//cin >> Documento;
	Documento = "mxnC.csv";

	MatrixXd matrizDada;
	matrizDada = openData(Documento);

	cout << "la matriz m es de tamano " << matrizDada.rows() << "x" << matrizDada.cols()  << " y es la siguiente: \n";
	cout << matrizDada << "\n";
	//a) Gauss Jordan

	cout << "la matriz m invertida es: \n" << gaussjordann(matrizDada) << endl << "\n";

	//b) Cofactores

	cout << "la matriz m invertida es: \n" << Cofactores(matrizDada) << endl << "\n";

	//CREAR ARCHIVOS CON RESULTADOS ---------------------------------------------------------

	saveData("matrizInvertidaGauss.csv", gaussjordann(matrizDada));
	saveData("matrizInvertidaEigen.csv", matrizDada.inverse());
	saveData("matrizInvertidaCofactores.csv", Cofactores(matrizDada));
	
}

