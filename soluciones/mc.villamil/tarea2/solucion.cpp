#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

typedef struct
{
    double **datos;
    int f;
    int c;
}Matrix;

Matrix inicial(int filas, int cols) 
{
    Matrix M;
    M.f = filas;
    M.c = cols;
    M.datos = new double*[filas];
    for (int i = 0; i < filas; i++) 
    {
        M.datos[i] = new double[cols];
        for (int j = 0; j < cols; j++) 
        {
            M.datos[i][j] = 0.0;
        }
    }
    return M;
}

Matrix inicialRand (int filas, int cols) 
{
    Matrix M;
    M.f = filas;
    M.c = cols;
    M.datos = new double*[filas];
    for (int i = 0; i < filas; i++)
    {
        M.datos[i] = new double[cols];
        for (int j = 0; j < cols; j++) 
        {
            M.datos[i][j] = rand()%10;
        }
    }
    return M;
}


Matrix MatrizIdentidad(int filas, int cols) 
{
    Matrix M;
    M.f = filas;
    M.c = cols;
    M.datos = new double*[filas];
    for (int i = 0; i < filas; i++) 
    {
        M.datos[i] = new double[cols];
        for (int j = 0; j < cols; j++) 
        {
            M.datos[i][j] = 0.0;
        }
        M.datos[i][i] = 1.0;
    }
    return M;
}

void CambioFilas(Matrix M, int r1, int r2) 
{
    float aux;
    for (int i = 0; i < M.c; i++) 
    {
        aux = M.datos[r1][i];
        M.datos[r1][i] = M.datos[r2][i];
        M.datos[r2][i] = aux;
    }
}

void Multiplicacion(Matrix M, int r, float c) 
{
    for (int i = 0; i < M.c; i++) 
    {
        M.datos[r][i] *= c;
    }
}

void addFilas(Matrix M, int r1, int r2, float c)
{
    for (int i = 0; i < M.c; i++) 
    {
        M.datos[r1][i] += M.datos[r2][i] * c;
    }
}

Matrix clon(Matrix M) 
{
    Matrix N = inicial(M.f, M.c);
    for (int i = 0; i < M.f; i++) 
    {
        for (int j = 0; j < M.c; j++) 
        {
            N.datos[i][j] = M.datos[i][j];
        }
    }
    return N;
}

Matrix gaussjordan(Matrix A) 
{
    Matrix M = clon(A);
    Matrix Inv = MatrizIdentidad(M.f, M.c);
    if (M.f == M.c)
    {
        for (int i = 0; i < M.f; i++) 
        {
            if (M.datos[i][i] == 0) 
            {
                int r = 0;
                while (r < M.c && (M.datos[i][r] == 0 || M.datos[r][i] == 0)) 
                {
                    r++;
                }
                CambioFilas(M,i,r);
            }
            double c = 1.0 / M.datos[i][i];
            Multiplicacion(M, i, c);
            Multiplicacion(Inv, i, c);
            for (int j = 0; j < M.f; j++) 
            {
                if (i != j) {
                    c = -M.datos[j][i];
                    addFilas(M, j, i, c);
                    addFilas(Inv, j, i, c);
                }
            }
        }
    }
    else
    {
        printf("Error La matriz no es cuadrada \n");
        Inv.f = -1;
        Inv.c = -1;
        free(Inv.datos);
    }
    return Inv;
}



void printMatrix(Matrix M) 
{
    for (int i = 0; i < M.f; i++) 
    {
        for (int j = 0; j < M.c; j++) 
        {
            printf("%0.2f\t", M.datos[i][j]);
        }
        printf("\n");
    }
}

void saveMatrix(Matrix M, char* fileName) 
{
    FILE *fp;
    fopen_s(&fp, fileName, "w");
    char linea[80];
    if (fp != NULL) 
    {
        sprintf_s(linea, "%d\t%d\n", M.f, M.c);
        fputs(linea, fp);
        for (int i = 0; i < M.f; i++) 
        {
            for (int j = 0; j < M.c; j++)
            {
                sprintf_s(linea, "%.2f\t", M.datos[i][j]);
                fputs(linea, fp);
            }
            fputs("\n", fp);
        }
    }
    else 
    {
        printf("No se pudo abrir el archivo %s\n", fileName);
    }
    fclose(fp);
}


int main()
{
    cout << "Matriz generada de numeros al azar" << endl;
    Matrix A = inicialRand(3, 3);
    printMatrix(A);
    printf("\n");
    cout << "Matriz inversa por metodo de Gauss Jordan" << endl;
    Matrix Inv = gaussjordan(A);
    printMatrix(Inv);
    printf("\n");
    saveMatrix(A,"A.txt");
    saveMatrix(Inv,"Inv.txt");
    system("pause");
    cout << "Matriz inversa por el metodo de Cofactores" << endl;
    return 1;
}

