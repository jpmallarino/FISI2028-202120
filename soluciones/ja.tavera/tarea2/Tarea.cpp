#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <conio.h>
#include<vector>
using namespace std;
using namespace Eigen;

MatrixXd Data(string fileToOpen)
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

void InvertirGaussJordan()
{
    MatrixXd m = Data("Texto.txt"), I(m.rows(),m.rows());
    int c = m.rows();
    //Se crea la matriz identidad
    for (int x = 0; x < c; x++)
    {
        for (int y = 0; y < c; y++)
        {
            I(x, y) = 0;
            if (x == y)
            {
                I(x, y) = 1;

            }
        }
    }
    cout << "Matriz inicial:\n " << m << endl;
    cout << "Matriz identidad:\n " << I << endl;
    cout << m.cols()<<endl;  
    /*Para lograr que la diagonal de la matriz sea 1, se divide cada elemento de la diagonal por el mismo y por su
    fila correspondiente, igual con la matriz identidad.*/
    for (int x = 0; x < c; x++)
    {
        float v = m(x, x);

        for (int y = 0; y < c; y++)
        {

            m(x, y) = m(x, y)*(1/v);
            I(x, y) = I(x, y)*(1/v);
        }


        for (int j = 0; j < c; j++)
        {
            //verifico no estar en diagonal y empiezo a hacer GJ:
            if (x != j)
            {
                float  s = m(j, x);
                for (int k = 0; k < c; k++)
                {
                    m(j, k) = m(j, k) - (s * m(x, k));
                    I(j, k) = I(j, k) - (s * I(x, k));
                }


            }




        }
    }
    cout << "Inversa:\n " << I << endl;
    fstream archivo;
    archivo.open("Texto.txt", ios::app);
    if (archivo.is_open())
    {
        archivo <<"La inversa es: \n"<< I;
        archivo.close();
    }
}
   
int determinantecofactor(Matrix2d x)
{
    int resultado;
    resultado = x(0, 0) * x(1, 1) - x(0, 1) * (1, 0);
    return resultado;
}
    
void determinante(MatrixXd m)
{
    //intento de una funcion recursiva que calcula el determinante por cofactores.
     if (m.rows() == 2)
     {
         return determinantecofactor(m);
     }
    vector<int> f;
   
        for (int i = 0; i < m.rows(); i++)
        {
            for (int j = 0; j < m.rows(); j++)
            {
                for (int k = 0; k < m.rows(); k++)
                {
                    if ((j == i) && (k == 0))
                    {
                        continue;
                        
                    }
                    MatrixXd m_l(m.rows() - 1, m.rows() - 1);
                    m_l(l,i) = m(j, k);
                    f.push_back(m(j, k));
                }

            }
        }
    
        cout << int(f.size()) << endl;
}
int main() 
{

   
    InvertirGaussJordan();
    determinante(Data("Texto.txt"));
    return 0;

}