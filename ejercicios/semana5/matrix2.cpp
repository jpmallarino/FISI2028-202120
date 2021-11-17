#include <iostream>
#include <Eigen/Dense>
#include <string>
 
using Eigen::MatrixXd;
using namespace Eigen;
using namespace std;
 
int main()
{
  string name = "Juan pablo mallarino \n github.com";
  int n = 0, m = 0;
  // Bloque de codigo que lee el archivo y determina filas y columnas
  MatrixXd A(n,m);
  // Bloque de codigo que carga el archivo a la matriz
  MatrixXd m = MatrixXd::Random(10,10); // # reales PSEUDO-aleatorios entre -1 y 1
  cout << "Checkpoint 1: \n" << m << endl;
  cout << "Determinant of m:\n" << m.determinant() << endl;
  MatrixXd u_m = m.inverse();
  cout << "Inverse of m:\n" << u_m << endl;
  cout << "Test de valicez m^-1*m:\n" << u_m*m << endl;
  // No existe tal cosa como exactitud en computacion -> decimales
  // el cero en precision doble (double) -> 10^-15
  // -> es un reto!
  // LISP + Mathematica
  m = (m + MatrixXd::Constant(10,10,1.2)) * 50; // # reales aleatorios entre 10 y 110
  cout << "Checkpoint 2: m =\n" << m << endl; // endl hace flush...
  VectorXd v(10);
  v << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
  cout << "Checkpoint 3: v =" << v << endl;
  cout << "m * v =" << endl << m * v << endl;
  cout << "terminando... "<<name<<endl;
  return 0;
}