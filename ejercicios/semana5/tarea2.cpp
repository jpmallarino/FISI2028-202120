#include <iostream>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using namespace Eigen;
using namespace std;
 

// -> https://aleksandarhaber.com/eigen-matrix-library-c-tutorial-saving-and-loading-data-in-from-a-csv-file/
// -> https://stackoverflow.com/questions/20786220/eigen-library-initialize-matrix-with-data-from-file-or-existing-stdvector
int main()
{
  MatrixXd m = MatrixXd::Random(3,3);
  m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
  cout << "m =" << endl << m << endl;
  VectorXd v(3);
  v << 1, 2, 3;
  cout << "m * v =" << endl << m * v << endl;
}