#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace fisi2028{
    unsigned int n = 0;
    double e_x = 0;
    double e_x2 = 0;
    double e_x3 = 0;
    double e_x4 = 0;

    void accumulate(double x){ }
}

int main(void){
    // scope: main (funcion)
    ofstream file; // Output File STREAM

    file.open("output.txt");

    int n_el = 0;

    file.close();

    return 0;
}
