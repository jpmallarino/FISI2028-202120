#include <iostream>
#include <fstream>

using namespace std;

namespace fisi2028{
    void mean(double *x_el){ }
}

int main(void){
    // Review the averages problem
    double *x_el;
    double *y_el;

    int n_el=0;
    cout<<"Num of elements? "; cin>>n_el;
    x_el = new double[n_el];
    y_el = new double[n_el];

    delete [] x_el;
    x_el = nullptr; // Forma segura de borrar rastro! (hackers)
    delete [] y_el;
    y_el = nullptr;
    return 0;
}
