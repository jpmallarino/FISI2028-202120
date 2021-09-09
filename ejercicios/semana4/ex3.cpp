#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Vector {
    double *v;
    uint n;
};

string print_vector(int* v, int);

int main(void){
    // Review the averages problem
    cout<< "Vamos a crear nuestra primera estructura!"<<endl;
    Vector A;
    cout<<"Tamaño de A: "<<sizeof(A)<<" bits."<<endl;
    return 0;
}


#ifndef V_PRINT_WRAP_NUM // OJO: esto es de procesador
#define V_PRINT_WRAP_NUM 8
#endif
#ifndef V_PRINT_MAX_ROWS
#define V_PRINT_MAX_ROWS 16
#endif
string print_vector(int* v, int n){
    ostringstream ss;
    ss << "[" << ( n > V_PRINT_WRAP_NUM ? "\n    ":"  ");
    for(int it = 0; it < n; it++){
        ss << v[it] << (it != n-1 ? ", ":"\0");
        if( (it+1) % V_PRINT_WRAP_NUM == 0 && it < n-1 )
            ss << "\n    ";
        if( V_PRINT_MAX_ROWS > 0 && \
                it == V_PRINT_MAX_ROWS*V_PRINT_WRAP_NUM ){
            ss << "...";
            break;
        }
    }
    ss << ( n > V_PRINT_WRAP_NUM ? "\n":"  ") << "]";
    return ss.str();
}
