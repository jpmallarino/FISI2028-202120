#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;


int inversa[3][3];

int main()
{
    ifstream Matriz ("Matriz.txt"); // Lee el archivo
    string fila;
    string fila_2;
    int dimension = 0;
    int numeros = 0;
    
    if(Matriz.fail()) //Si falla el archivo, termina el programa
    {
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }
    
    if (Matriz.is_open())// Me dice la dimensión de la matriz
    {   
        while ( getline (Matriz,fila) )
        {
            cout << fila << '\n';
            ++dimension;
        }
        Matriz.close();
    }
    
    string strfilas[dimension];
        
    Matriz.open ("Matriz.txt");
    
    int temp=0;
    
    while (getline (Matriz,fila_2) )
    {
        strfilas[temp] = fila_2;
        ++temp;
    }
    
    Matriz.close();
    
    for (int i=0; i<dimension; i++)
    {
      cout << "Fila ["<<i<< "]: " << strfilas[i]  <<endl;
    }
    
    int matriz[dimension][dimension];
    int numeroij =0;
    
    cout << "Matriz: "<< endl;
    
    
    for (int i=0; i<dimension; i++)
    {
        for (int j=0; j< (dimension + 1); j= j+2)
        {
            numeroij = strfilas[i][j] - 48; 
            matriz[i][j] = numeroij;
            cout << matriz[i][j] <<" "<< endl;
        }
       
    }


    return 0;    
}
