#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
 
using namespace std;
using namespace Eigen;

// lee la matriz desde el archivo de texto path. Números separados por espacios
MatrixXd load_matrix(string path) {
	vector <double> raw_data;
	ifstream file(path);
	string line, element;
	stringstream ss;
	int rows=0,cols=0;
	
	while ( getline(file,line) ) { // leer línea del archivo
		ss = stringstream(line); // convertir la línea en un stream
		while( ss >> element ) { // leer cada elemento de la línea, separado por espacios
			raw_data.push_back(stod(element)); // convertir a double y echar al vector
		}
		rows++; // por cada fila terminada se aumenta el número de filas
	}
	file.close();
	cols = raw_data.size()/rows;
	return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(raw_data.data(),rows,cols);
}

// guarda la matriz como un archivo de texto en path. Números separados por espacios
void save_matrix(string path, MatrixXd matrix) {
	ofstream file(path);
	file << matrix; // echar matriz al archivo
	file.close();
}

// retorna una copia de la matriz M sin la fila dada por el índice
MatrixXd remove_row(MatrixXd M, int remove_index) {
	int rows = M.rows()-1;
	int cols = M.cols();
	M.block(remove_index,0,rows-remove_index,cols) = M.bottomRows(rows-remove_index);
	M.conservativeResize(rows,cols);
	return M;
}
// retorna una copia de la matriz M sin la columna dada por el índice
MatrixXd remove_col(MatrixXd M, int remove_index) {
	int rows = M.rows();
	int cols = M.cols()-1;
	M.block(0,remove_index,rows,cols-remove_index) = M.rightCols(cols-remove_index);
	M.conservativeResize(rows,cols);
	return M;
}
// retorna una copia de la matriz M sin la columna J y sin la fila I
MatrixXd minor_matrix(MatrixXd M, int I, int J) {
	return remove_col(remove_row(M,I),J);
}

// calcula el determinante de una matriz cuadrada M
double det(MatrixXd M){
	int rows = M.rows();
	int cols = M.cols();
	
	double d = 0.0;
	
	if (rows != cols) {
		cerr << "cannot take det of non-square matrix:" << endl << M << endl;
		abort();
	}
	else if (rows == 1 && cols == 1) {
		d = M(0,0);
	} else {
		for(int j=0; j<cols; j++){
			d += pow((-1.0),j) * M(0,j) * det(minor_matrix(M,0,j));
		}
	}
	return d;
}

// retorna el cofactor i,j de la matriz M
double cofactor(MatrixXd M, int i, int j){
	return pow(-1.0,i+j)*det(minor_matrix(M,i,j));
}

MatrixXd cramer_inverse(MatrixXd M) {
	double M_det = det(M);
	if (M_det == 0) {
		cout << "cannot take inverse of singular matrix:" << endl << M << endl;
		abort();
	}
	MatrixXd Adj(M); // Adjugate matrix
	int n = M.rows();
	
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			Adj(i,j) = cofactor(M,j,i); // note j,i, the transpose of the cofactor matrix
		}
	}
	
	return Adj/M_det;
}

// matriz elemental nxn para cambiar la fila i por la j
MatrixXd elemental_swap(int i, int j, int n){
	MatrixXd E = MatrixXd::Identity(n,n);
	E(i,i) = 0.;
	E(j,j) = 0.;
	E(i,j) = 1.;
	E(j,i) = 1.;
	return E;
}
// matriz elemental nxn para multiplicar la fila i por la constante k
MatrixXd elemental_multiplication(double k, int i, int n){
	MatrixXd E = MatrixXd::Identity(n,n);
	E(i,i) = k;
	return E;
}
// matriz elemental nxn para sumar k veces la fila j a la fila i
MatrixXd elemental_addition(double k, int i, int j, int n){
	MatrixXd E = MatrixXd::Identity(n,n);
	E(i,j) = k;
	return E;
}

MatrixXd gauss_jordan_inverse(MatrixXd M) {
	if (det(M) == 0) {
		cout << "cannot take inverse of singular matrix:" << endl << M << endl;
		abort();
	}
	int n = M.rows();
	int k;
	MatrixXd E = MatrixXd::Identity(n,n);
	MatrixXd E_new;
	
	// grant pivots
	for (int i=0; i<n; i++) {
		// k is the first row that is nonzero on column i
		k = i;
		while (M(k,i) == 0.0) { k++;}
		E_new = elemental_swap(k,i,n);
		E = E_new * E;
		M = E_new * M;
	}
	// put in triangular form
	for (int j=0; j<n; j++) {
		for (int i=j+1; i<n; i++) {
			if (M(i,j) != 0.0) {
				E_new = elemental_addition(-M(i,j)/M(j,j),i,j,n);
				E = E_new * E;
				M = E_new * M;
			}
		}
	}
	// force ones in diagonal
	for (int i=0; i<n; i++) {
		E_new = elemental_multiplication(1/M(i,i),i,n);
		E = E_new * E;
		M = E_new * M;
	} 
	// backsubstitute
	for (int j=n-1; j>=0; j--) {
		for (int i=0; i<j; i++) {
			//cout << i << " " << j << endl;
			E_new = elemental_addition(-M(i,j),i,j,n);
			E = E_new * E;
			M = E_new * M;
		}
	}
	
	return E;
}

int main(int argc, char *argv[]) {
	
	string input_filename;
	
	if (argc == 2) {
		input_filename = (string)argv[1];
	} else {
		cout << "Insert filename for input matrix: ";
		cin >> input_filename;
	}
	
	MatrixXd m = load_matrix(input_filename);
	
	save_matrix("eigen.dat",m.inverse());
	save_matrix("gauss_jordan.dat",gauss_jordan_inverse(m));
	save_matrix("cramer.dat",cramer_inverse(m));
}