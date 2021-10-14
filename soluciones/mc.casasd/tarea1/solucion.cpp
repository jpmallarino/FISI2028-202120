
/* 
 * Asignatura: Métodos Computacionales en Ciencias
 * Nombre: María Camila Casas Díaz
 * Código: 201813057
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

MatrixXd LeerMatrizIngresada(string path) {
	vector <double> data;
	fstream file(path);
	string line, value;
	int filas=0;
	int columnas=0;
	
	while (getline(file,line)) {
		stringstream ss (line);
		while( ss >> value ) { 
			data.push_back(stod(value));
		}
		filas++;
	}
	file.close();
	columnas = data.size()/filas;
	return Map<Matrix<double,Dynamic,Dynamic,RowMajor>>(data.data(),filas,columnas);
}

double determinante(MatrixXd Matriz) {
	double det = Matriz.determinant();
	return det;
}

MatrixXd MatrizFilaElimiadaI(MatrixXd Matriz, int i) {
	int filas = Matriz.rows()-1;
	int columnas = Matriz.cols();
	Matriz.block(i,0,filas-i,columnas) = Matriz.bottomRows(filas-i);
	Matriz.conservativeResize(filas,columnas);
	return Matriz;
}

MatrixXd MatrizColumnaEliminadaJ(MatrixXd Matriz, int j) {
	int filas = Matriz.rows();
	int columnas = Matriz.cols()-1;
	Matriz.block(0,j,filas,columnas-j) = Matriz.rightCols(columnas-j);
	Matriz.conservativeResize(filas,columnas);
	return Matriz;
}

MatrixXd submatriz(MatrixXd Matriz, int i, int j) {
	return MatrizFilaElimiadaI(MatrizColumnaEliminadaJ(Matriz,j),i);
}

double cofactor(MatrixXd Matriz, int i, int j) {
	return pow(-1,i+j)*determinante(submatriz(Matriz,i,j));
}

MatrixXd Multiplicacion(double k, int i, int n){
	MatrixXd Matriz = MatrixXd::Identity(n,n);
	Matriz(i,i) = k;
	return Matriz;
}

MatrixXd Suma(double k, int i, int j, int n){
	MatrixXd Matriz = MatrixXd::Identity(n,n);
	Matriz(i,j) = k;
	return Matriz;
}

MatrixXd Intercambio(int i, int j, int n){
	MatrixXd Matriz = MatrixXd::Identity(n,n);
	Matriz(i,i) = 0;
	Matriz(i,j) = 1;
	Matriz(j,j) = 0;
	Matriz(j,i) = 1;
	return Matriz;
}

MatrixXd InversaGaussJordan(MatrixXd Matriz) {
	
	if (determinante(Matriz) == 0) {
		cout << "La Matriz es singular, det = " << determinante(Matriz) << endl; abort();
	}
	int n = Matriz.rows(), k;
	MatrixXd MatrizIdentidad = MatrixXd::Identity(n,n);
	MatrixXd Cambios;
	
	for (int i=0; i<n; i++) {
		k = i;
		while (Matriz(k,i) == 0.0) { 
			k++;
			}
			
		Cambios = Intercambio(k,i,n);
		MatrizIdentidad = Cambios * MatrizIdentidad;
		Matriz = Cambios * Matriz;
	}

	for (int j=0; j<n; j++) {
		for (int i=j+1; i<n; i++) {
			if (Matriz(i,j) != 0.0) {
				Cambios = Suma(-Matriz(i,j)/Matriz(j,j),i,j,n);
				MatrizIdentidad = Cambios * MatrizIdentidad;
				Matriz = Cambios * Matriz;
			}
		}
	}
	
	for (int i=0; i<n; i++) {
		Cambios = Multiplicacion (1/Matriz(i,i),i,n);
		MatrizIdentidad = Cambios * MatrizIdentidad;
		Matriz = Cambios * Matriz;
	} 
	
	for (int j=n-1; j>=0; j--) {
		for (int i=0; i<j; i++) {
			Cambios = Suma (-Matriz(i,j),i,j,n);
			MatrizIdentidad = Cambios * MatrizIdentidad;
			Matriz = Cambios * Matriz;
		}
	}
	/* 
	resultado;
	Matriz = MatrizIdentidad
	MatrizIdentidad = Inversa  
	*/
	return MatrizIdentidad;
}

MatrixXd InversaCramer(MatrixXd Matriz) {
	MatrixXd adjunta(Matriz);
	int n = Matriz.cols(); 
	double det = determinante(Matriz);

	if (det == 0) {
		cout << "La Matriz es singular, det = " << determinante(Matriz) << endl; abort();
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			adjunta(i,j) = cofactor(Matriz,j,i); 
		}
	}
	MatrixXd ICramer = adjunta/det;
	return ICramer;
}

MatrixXd InversaEigen(MatrixXd Matriz) {
	double det = determinante(Matriz);
	if (det == 0) {
		cout << "La Matriz es singular, det = " << determinante(Matriz) << endl; abort();
	}
	MatrixXd Ieigen = Matriz.inverse();
	return Ieigen;
}

void saveData(string archivo, MatrixXd matriz) {
	ofstream file(archivo);
	file << matriz; file.close();
}

int main() {
	string archivo;
	cout << "Inserte un Archivo que contenga la matriz cuya inversa quiera calcular: "; cin >> archivo;
	MatrixXd matriz = LeerMatrizIngresada(archivo);
	saveData("InversaGaussJordan.txt",InversaGaussJordan(matriz));
	saveData("InversaCramer.txt",InversaCramer(matriz));
	saveData("InversaEigen.txt",InversaEigen(matriz));

}

