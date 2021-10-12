#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include <type_traits>

using namespace std;
using namespace Eigen;

//Código que abre el archivo
MatrixXd openData(string fileToOpen)
{
 
    vector <double> matrixEntries;
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

//Código que guarda el archivo

void saveData(string fileName, MatrixXd  matrix)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, " ", "\n");
    ofstream file(fileName);
    if (file.is_open())
    {
        file << matrix.format(CSVFormat);
        file.close();
    }
}


//Inversa por Gauss Jordan

void Print(MatrixXd n, int t, int k)
{
    FILE *output_file;
    output_file=fopen("InversaGJ.txt", "w");
    
    for (int b = 0; b < t; b++) {
        for (int t = n; t < k; j++) {
           fprintf(output_file,"%.3f  ", n(b,t));
        }
        fprintf(output_file,"\t");
    }
   
     return;
}


void GaussJordan(MatrixXd m){
    
    
    
   MatrixXd I_ = MatrixXd::Identity(m.rows(),m.cols());
   
   MatrixXd C(m.rows(), m.cols()+I_.cols());
    
   C << m, I_;
    
   C.row(0).swap(C.row(m.rows() - 1));
    
   for (int i = 0; i < m.rows(); i++) {

        for (int j = 0; j < m.rows(); j++) {

            if (j != i) {

                float temp = C(j,i) / C(i,i);
                for (int k = 0; k < 2*m.rows(); k++) {

                    C(j,k) -= C(i,k)*temp;
                }
            }
        }
    }
    
    
    for (int i = 0; i < m.rows(); i++) {

        float temp_ = C(i,i);
        
        for (int j = 0; j < 2 * m.rows(); j++) {

            C(i,j) = C(i,j)/temp_;
        }
    
    
    }

    Print(C, m.cols(), 2*m.cols());
}



