#include <iostream>
#include <eigen-3.4.0/Eigen/Dense>
 
using Eigen::MatrixXd;
using namespace Eigen;
using namespace std;
 

// -> https://aleksandarhaber.com/eigen-matrix-library-c-tutorial-saving-and-loading-data-in-from-a-csv-file/
// -> https://stackoverflow.com/questions/20786220/eigen-library-initialize-matrix-with-data-from-file-or-existing-stdvector



MatrixXd identidad(int filas, int cols) {
	MatrixXd M;
	M.resize(filas, cols);
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < cols; j++) {
			M(i,j) = 0.0;
		}
		M(i,i) = 1.0;
	}
	return M;
}





int main()
{
  MatrixXd m = MatrixXd::Random(3,3);
  m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
  cout << "m =" << endl << m << endl;
  //VectorXd v(3);
  //v << 1, 2, 3;
  //cout << "m * v =" << endl << m * v << endl;

  cout << "la matriz m es de tamano:  " << m.rows() << "x" << m.cols() << endl << "\n";

  cout << "la matriz identidad: \n" << identidad(4, 4) << endl;

}
 
