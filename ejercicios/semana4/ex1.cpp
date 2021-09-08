#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int* fib_cache;
int fib_cache_n=0; // el elemento que se ha calculado y guardado
uint fib_cache_calls = 0;
int f_fibonacci_cache(int n){
    fib_cache_calls++;
    if(n <= fib_cache_n)
        return fib_cache[n];
    if(n == 1 || n == 0){
        fib_cache[0] = 1;
        fib_cache[1] = 1;
        fib_cache_n = 2;
        return 1;
    } else {
        int f_nm1,f_nm2;
        f_nm1 = f_fibonacci_cache(n-1);
        f_nm2 = f_fibonacci_cache(n-2);
        fib_cache[n] = f_nm1 + f_nm2;
        fib_cache_n = n+1;
        return f_nm1 + f_nm2;
    }
}

uint fib_calls = 0;
int f_fibonacci(int n){
    fib_calls++;
    if (n == 0 || n == 1)
        return 1;
    return f_fibonacci(n-1)+f_fibonacci(n-2);
}

string print_vector(int* v, int);

int main(void){
    // Review the averages problem
    int fib_n;
    cout<<"cual elemento desea calcular? "; cin>>fib_n;
    // dimensionar el vector dinamico
    fib_cache = new int[fib_n];
    cout<<"el elemento "<<fib_n<<" es "<<f_fibonacci(fib_n)<<endl;
    cout<<"\tllamados recursivos: "<<fib_calls<<endl;
    cout<<"el elemento "<<fib_n<<" es (cache) "<<f_fibonacci_cache(fib_n)<<endl;
    cout<<"\tllamados recursivos: "<<fib_cache_calls<<endl;
    if(fib_cache){
        cout<<"deleting fib cache!"<<endl;
        cout<<"::cache:: "<<print_vector(fib_cache,fib_n)<<endl;
        delete [] fib_cache, fib_cache = nullptr;
    }
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
