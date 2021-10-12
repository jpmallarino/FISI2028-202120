/*
author: jivfur
date:11/12/2017
Descripcion:
V1: Definicion de la estructura, Inicialización
V2: Producto de Dos Matrices
V3: Inversa e Identidad
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	double **datos;
	int fil;
	int col;
}Matrix;

Matrix inicializa(int filas, int cols) {
	Matrix M;
	M.fil = filas;
	M.col = cols;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = 0.0;
		}
	}
	return M;
}

Matrix inicializaRandom(int filas, int cols) {
	Matrix M;
	M.fil = filas;
	M.col = cols;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = rand()%10;
		}
	}
	return M;
}


Matrix identidad(int filas, int cols) {
	Matrix M;
	M.fil = filas;
	M.col = cols;
	M.datos = new (double*[filas]);
	for (int i = 0; i < filas; i++) {
		M.datos[i] = new (double[cols]);
		for (int j = 0; j < cols; j++) {
			M.datos[i][j] = 0.0;
		}
		M.datos[i][i] = 1.0;
	}
	return M;
}

void switchRows(Matrix M, int r1, int r2) {
	float aux;
	for (int i = 0; i < M.col; i++) {
		aux = M.datos[r1][i];
		M.datos[r1][i] = M.datos[r2][i];
		M.datos[r2][i] = aux;
	}
}

void multiplyRowConstant(Matrix M, int r, float c) {
	for (int i = 0; i < M.col; i++) {
		M.datos[r][i] *= c;
	}
}

void addRows(Matrix M, int r1, int r2, float c) {
	for (int i = 0; i < M.col; i++) {
		M.datos[r1][i] += M.datos[r2][i] * c;
	}
}

Matrix clone(Matrix M) {
	Matrix N = inicializa(M.fil, M.col);
	for (int i = 0; i < M.fil; i++) {
		for (int j = 0; j < M.col; j++) {
			N.datos[i][j] = M.datos[i][j];
		}
	}
	return N;
}

Matrix gaussjordan(Matrix A) {
	Matrix M = clone(A);
	Matrix Inv = identidad(M.fil, M.col);
	if (M.fil == M.col) {
		for (int i = 0; i < M.fil; i++) {
			if (M.datos[i][i] == 0) {
				int r = 0;
				while (r < M.col && (M.datos[i][r] == 0 || M.datos[r][i] == 0)) {
					r++;
				}
				switchRows(M,i,r);
			}
			double c = 1.0 / M.datos[i][i];
			multiplyRowConstant(M, i, c);
			multiplyRowConstant(Inv, i, c);
			for (int j = 0; j < M.fil; j++) {
				if (i != j) {
					c = -M.datos[j][i];
					addRows(M, j, i, c);
					addRows(Inv, j, i, c);
				}
			}
		}
	}else {
		printf("Error La matriz no es cuadrada \n");
		Inv.fil = -1;
		Inv.col = -1;
		free(Inv.datos);
	}
	return Inv;
}



void printMatrix(Matrix M) {
	for (int i = 0; i < M.fil; i++) {
		for (int j = 0; j < M.col; j++) {
			printf("%0.2f\t", M.datos[i][j]);
		}
		printf("\n");
	}
}

Matrix producto(Matrix A, Matrix B) {
	Matrix C = inicializa(A.fil,B.col);
	if (A.col == B.fil) {
		for (int i = 0; i < A.fil; i++) {
			for (int j = 0; j < A.col; j++) {
				for (int k = 0; k < B.col; k++) {
					C.datos[i][k] += A.datos[i][j] * B.datos[j][k];
				}
			}
		}
	}
	else {
		printf("Error: Las Matrices no tienen la dimension requerida\n");
		C.fil = -1;
		C.col = -1;
		free(C.datos);
	}
	return C;
}


int main() {
	Matrix A = inicializaRandom(4, 4);
	Matrix Inv = gaussjordan(A);	
	printMatrix(A);
	printf("\n");
	printMatrix(Inv);
	printf("\n");
	Matrix C = producto(A, Inv);
	Matrix H = identidad(4,4);
	printMatrix(C);
	printMatrix(H);
	system("pause");
	return 1;
}