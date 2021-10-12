#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include <type_traits>

using namespace std;
using namespace Eigen;



//Codigo par abrir el archivo

MatrixXd openData(string fileToOpen)
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

//Codigo para guardar el archivo en cualquier formato 

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

void Print(MatrixXd a, int n, int m)
{
    FILE *output_file;
    output_file=fopen("Inversa_Gauss_Jordan.txt", "w");
    
    for (int i = 0; i < n; i++) {
        for (int j = n; j < m; j++) {
           fprintf(output_file,"%.3f  ", a(i,j));
        }
        fprintf(output_file,"\n");
    }
   
     return;
}


void Gauss(MatrixXd m){
    
    
    
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

//Inversa por cofactores 

void getCofactor(int** A , int** temp , int p, int q, int n)
{
    int i = 0, j = 0;
    
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
           
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(int**A, int n)
{
    int D = 0; 
    if (n == 1)
        return A[0][0];

    int** temp = new int* [n];
    for (int i = 0; i < n; i++) {
        temp[i] = new int[n];
    }

    int sign = 1;  
    for (int f = 0; f < n; f++)
    {
       
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        
        sign = -sign;
    }

    return D;
}

void adjoint(int** A, int** adj, int N)
{
   
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    
    int sign = 1;
    int** temp = new int* [N];
    for (int i = 0; i < N; i++) {
        temp[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            
            getCofactor(A, temp, i, j, N);

            
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}

MatrixXd inverse(MatrixXd m, int N)
{  
    
    int rows = m.rows();
    int cols = m.cols();
    int** matrix = new int* [rows];
    
    for (int i = 0; i < rows; i++) 
    {
        matrix[i] = new int[cols];
    }
    
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            *(*(matrix + i) + j) = m(i, j);

    float** aux = new float* [rows];
    
    for (int i = 0; i < rows; i++) {
        aux[i] = new float[cols];
    }
    
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            *(*(aux + i) + j) = m(i, j);
    
    MatrixXd mx(N, N);
    
    int det = determinant(matrix, N);

    int** adj = new int* [N];
    for (int i = 0; i < N; i++) 
        adj[i] = new int[N]; 
    adjoint(matrix, adj,N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            aux[i][j] = adj[i][j] / float(det);

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            mx(j, i) = aux[j][i];
            
        }
    }
    return mx;

}

//Otra forma de encontrar la inversa 
//En vez de encontrar un vecotor dinamico lo que hacemos es trabajar directamente con MatrixXd 

/*

int determ(MatrixXd m,int n)
  {
    
  int det=0, p, h, k, i, j;
  MatrixXd temp =  MatrixXd::Zero(m.rows(),m.cols());
    
  if(n==1) {
    return m(0,0);
  } 
  
  else if(n==2){
    det=(m(0,0)*m(1,1)-m(0,1)*m(1,0));
    return det;
  } 
  
  else {
    for(p=0;p<n;p++) {
      h = 0;
      k = 0;
      for(i=1;i<n;i++) {
        for( j=0;j<n;j++) {
          if(j==p) {
            continue;
          }
            
          temp(h,k) = m(i,j);
          k++;
            
          if(k==n-1) {
            h++;
            k = 0;
          }
        
        }
      }
        
      det=det+m(0,p)*pow(-1,p)*determ(temp,n-1);
    }
      
    return det;
  }

}  




void cofact(MatrixXd m, int n)
{
    int i = 0, j = 0;
   
    MatrixXd temp = MatrixXd::Zero(m.rows(),m.cols());
    MatrixXd adj = MatrixXd::Zero(m.rows(),m.cols());
 
    for (int  p = 0; p<n; p++){
       
        for (int q = 0; q<n; q++){
   
            for (int row = 0; row < n; row++){
               
                for (int col = 0; col < n; col++){
           
                        if (row != q && col != p){
                           
                            temp(i,j) = m(row,col);

                                if (j == n - 1)
                                {
                                    j = 0;
                                    i++;
                                }

                     }
       
                }
   
         }
           
        adj(q,p) = pow(-1,q+p)*determ(temp,n - 1);

      }
       
       
    }

} 

Cabe destacar que el principal problema recido en que la adjunta da una matriz de ceros, por lo que no es posible encontrar la inversa


void Inverse(MatrixXd m, MatrixXd adj, int n){
    
    int i;
    int j;
    
    MatrixXd b = MatrixXd::Zero(m.rows(),m.cols());
    MatrixXd I_ = MatrixXd::Zero(m.rows(),m.cols());
    
    for (i=0;j<n;i++){
            
        for (j = 0; j<n; j++){
            
                b(i,j) = adj(j,i);
            
            
        }
        
    }
    
    //int d = determ(m,n);
    
   
    for (i=0;j<n;i++){
            
        for (j = 0; j<n; j++){
            
                I_(i,j) = b(i,j)/d;
            
            
        }
        
    }
    
   cout << I_ << endl;
    
}


*/


int main(){
    
    MatrixXd data_;
    data_ = openData("nums.txt");
    
    cout << "Matriz" << endl;
    cout << data_ << endl;
    
    Gauss(data_);
    
    MatrixXd cofact = inverse(data_, data_.rows());
    saveData("Inversa_por_cofactores.txt",cofact);
    
    MatrixXd Eigen_ = data_.inverse();
    saveData("Inversa_Eigen.txt",Eigen_);
    
    
    return 0;
}