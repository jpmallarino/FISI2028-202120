#include <iostream>
using namespace std;

int numposibilidades (int n, int j)
{
    variable[0]=1;
    int cont =0;
    
    for (int i=1; i<=n; i++)
    {
        int x =i + j - 1;
        int x_2= i-1;
        
        if (x >= 0)
        {
            cont -= variable[x];
        }
        cont += variable[x_2];
        variable[i] = cont;
    }
    return variable[n];
}

int main ()
{
   cout << numposibilidades <<endl;
}