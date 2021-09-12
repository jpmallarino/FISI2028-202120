#include <iostream>
#include <fstream>

using namespace std;

int fib_calls = 0;
int f_fibonacci(int n){
    fib_calls++;
    if (n == 0 || n == 1)
        return 1;
    return f_fibonacci(n-1)+f_fibonacci(n-2);
}

int main(void){
    // Review the averages problem
    int fib_n;
    cout<<"cual elemento desea calcular? "; cin>>fib_n;
    // dimensionar el vector dinamico
    cout<<"el elemento "<<fib_n<<" es "<<f_fibonacci(fib_n)<<endl;
    cout<<"\tllamados recursivos: "<<fib_calls<<endl;
    return 0;
}
