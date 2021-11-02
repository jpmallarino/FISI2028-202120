#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

typedef struct
{
    double **datos;
    int fila;
    int columna;
}

Matrix;

int filas = 0;
int columnas = 0;

Matrix inicializa(int filas, int columnas) 
{
    Matrix M;
    M.fila = filas;
    M.columna = columnas;
    M.datos = new double*[filas];
    
    for (int i = 0; i < filas; i++) 
    {
        M.datos[i] = new double[columnas];
        for (int j = 0; j < columnas; j++) 
        {
            M.datos[i][j] = 0.0;
        }
    }
    return M;
}


Matrix identidad(int filas, int columnas)
{
    Matrix M;
    M.fila = filas;
    M.columna = columnas;
    M.datos = new double*[filas];
    
    for (int i = 0; i < filas; i++) 
    {
        M.datos[i] = new double[columnas];
        for (int j = 0; j < columnas; j++) 
        {
            M.datos[i][j] = 0.0;
        }
        M.datos[i][i] = 1.0;
    }
    return M;
}

void cambioFila(Matrix M, int fila1, int fila2) 
{
    float aux;
    for (int i = 0; i < M.columna; i++)
    {
        aux = M.datos[fila1][i];
        M.datos[fila1][i] = M.datos[fila2][i];
        M.datos[fila2][i] = aux;
    }
}

void multiplicarFila(Matrix M, int fila, float c) 
{
    for (int i = 0; i < M.columna; i++)
    {
        M.datos[fila][i] *= c;
    }
}

void sumarFila(Matrix M, int fila1, int fila2, float c)
{
    for (int i = 0; i < M.columna; i++)
    {
        M.datos[fila1][i] += M.datos[fila2][i] * c;
    }
}

Matrix clone(Matrix M) 
{
    Matrix N = inicializa(M.fila, M.columna);
    
    for (int i = 0; i < M.fila; i++) 
    {
        for (int j = 0; j < M.columna; j++) 
        {
            N.datos[i][j] = M.datos[i][j];
        }
    }
    
    return N;
}

Matrix gaussjordan(Matrix A) 
{
    Matrix M = clone(A);
    Matrix Inv = identidad(M.fila, M.columna);
    
    if (M.fila == M.columna) 
    {
        for (int i = 0; i < M.fila; i++)
        {
            if (M.datos[i][i] == 0) 
            {
                int fila = 0;
                
                while (fila < M.columna && (M.datos[i][fila] == 0 || M.datos[fila][i] == 0)) 
                {
                    fila++;
                }
                cambioFila(M,i,fila);
            }
            double c = 1.0 / M.datos[i][i];
            multiplicarFila(M, i, c);
            multiplicarFila(Inv, i, c);
            for (int j = 0; j < M.fila; j++)
            {
                if (i != j)
                {
                    c = -M.datos[j][i];
                    sumarFila(M, j, i, c);
                    sumarFila(Inv, j, i, c);
                }
            }
        }
    }
    else 
    {
        printf("Error La matriz no es cuadrada \n");
        Inv.fila = -1;
        Inv.columna = -1;
        free(Inv.datos);
    }
    return Inv;
}



void imprimirMatrix(Matrix M) 
{
    for (int i = 0; i < M.fila; i++)
    {
        for (int j = 0; j < M.columna; j++) 
        {
            printf("%0.2f\t", M.datos[i][j]);
        }
        printf("\n");
    }
}


Matrix leerMatrix(const char* Matriz) 
{
    Matrix M;
    FILE *fp;
    fopen(Matriz, "r");
    char linea[20];
    char *nextToken;
    /*
    INT INT
    FLOAT FLOAT ... FLOAT
    FLOAT FLOAT ... FLOAT
    :
    FLOAT FLOAT ... FLOAT
    */
    if (fp != NULL) 
    {
        fgets(linea, 19, fp);
        char *ptr = strtok(linea,"\t");
        int f = atoi(ptr);
        int c = atoi(strtok(NULL, "\t"));
        M = inicializa(f, c);
        f = 0;
        
        while (!feof(fp))
        {
            fgets(linea, 19, fp);
            c = 0;
            ptr= strtok(linea, "\t");
            while (ptr != NULL && c < M.columna && f < M.fila) 
            {
                M.datos[f][c] = atof(ptr);
                c++;
                ptr = strtok(NULL, "\t\n");
            }
            f++;
        }

    }

    fclose(fp);

    return M;
}

int main()
{
    Matrix A = leerMatrix("Matriz.txt");
    Matrix Inv = gaussjordan(A);
    imprimirMatrix(A);
    printf("\n");
    imprimirMatrix(Inv);
    printf("\n");
    return 1;
}