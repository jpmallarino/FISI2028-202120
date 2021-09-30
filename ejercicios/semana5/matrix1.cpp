#include <iostream>
#include <Eigen/Dense>

// from numpy import random
using Eigen::MatrixXd; // Objeto que me crea una matriz DINAMICA
using namespace std;

int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  cout << m << endl;
}