#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define BUFF  ((int) 1500)

MatrixXd Matriz(const char *documento)
{
    int cols = 0, rows = 0;
    double buff[BUFF];

    
    ifstream infile;
    infile.open(documento);
    while (!infile.eof())
    {
        string line;
        getline(infile, line);

        int temp_cols = 0;
        stringstream stream(line);
        while (!stream.eof())
            stream >> buff[cols * rows + temp_cols++];

        

        if (cols == 0)
            cols = temp_cols;

        rows++;
    }

    infile.close();

    rows--;

    
    MatrixXd result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i, j) = buff[cols * i + j];

    return result;
};

void InvertirGaussJordan()
{
    MatrixXd m = Matriz("Texto.txt"), I(m.rows(), m.rows());

    //Se crea la matriz identidad
    for (int x = 0; x < m.rows(); x++)
    {
        for (int y = 0; y < m.rows(); y++)
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
    //Para lograr que la diagonal de la matriz sea 1, se divide cada elemento de la diagonal por el mismo y por su
    //fila correspondiente, igual con la matriz identidad.
    for (int x = 0; x < m.rows(); x++)
    {
        float v = m(x, x);

        for (int y = 0; y < m.rows(); y++)
        {

            m(x, y) = m(x, y) / v;
            I(x, y) = I(x, y) / v;
        }


        for (int j = 0; j < m.rows(); j++)
        {
            //verifico no estar en diagonal y empiezo a hacer GJ:
            if (x != j)
            {
                float  s = m(j, x);
                for (int k = 0; k < m.rows(); k++)
                {
                    m(j, k) = m(j, k) - s * m(x, k);
                    I(j, k) = I(j, k) - s * I(x, k);
                }


            }




        }
    }
    cout << "Inversa:\n " << I << endl;
    fstream archivo;
    archivo.open("Texto.txt", ios::app);
    if (archivo.is_open())
    {
        archivo << I;
        archivo.close();
    }
}
   
        
    
    

int main() 
{

   
    InvertirGaussJordan();
    return 0;

}