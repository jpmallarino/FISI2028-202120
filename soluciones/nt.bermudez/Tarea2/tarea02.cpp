#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include <type_traits>

using namespace std;
using namespace Eigen;

MatrixXd open(string fileToOpen)
{
    vector<double> MtxEntries;
    ifstream MtxDataFile(fileToOpen);
    string MtxRowString;
    string MtxEntry;
 
    int MtxRowNumber = 0;
  
    while (getline(MtxDataFile, MtxRowString))
    {
        stringstream MtxRowStringStream(MtxRowString);
 
        while (getline(MtxRowStringStream, MtxEntry, ',')) 
        {
            MtxEntries.push_back(stod(MtxEntry));  
        }
        MtxRowNumber++; 
    }
 
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);
 }

void save(string fileName, MatrixXd  matrix)
{
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, " ", "\n");
    ofstream file(fileName);
    if (file.is_open())
    {
        file << matrix.format(CSVFormat);
        file.close();
    }
}

void Print(MatrixXd a, int n, int m)
{
     for (int i = 0; i < n; i++) 
{       
	 for (int j = n; j < m; j++) 
{
            printf("%.3f  ", a(i, j));
        }
        fprintf(output_file,"\n");
    }
   
     return;
}


void GaussJordan(MatrixXd mtx){
    
   MatrixXd I_ = MatrixXd::Identity(mtx.rows(),mtx.cols());
   
   MatrixXd C(mtx.rows(), mtx.cols()+I_.cols());
    
   C << mtx, I_;
    
   C.row(0).swap(C.row(mtx.rows() - 1));
    
   for (int i = 0; i < mtx.rows(); i++) {

        for (int j = 0; j < mtx.rows(); j++) 
{
            if (j != i) {

                float temp = C(j,i) / C(i,i);
                for (int k = 0; k < 2*mtx.rows(); k++) 
{
                    C(j,k) -= C(i,k)*temp;
                }
            }
        }
    }
    
    for (int i = 0; i < mtx.rows(); i++)
{
        float temp_ = C(i,i);
        
        for (int j = 0; j < 2 * mtx.rows(); j++) 
{
            C(i,j) = C(i,j)/temp_;
        }
      }

    Print(C, mtx.cols(), 2*mtx.cols());
}



