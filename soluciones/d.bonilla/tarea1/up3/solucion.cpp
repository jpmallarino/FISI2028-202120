#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int maneras(int n);

int main( void )
{

    int n = 0;

    cout << "Ingrese el numero de escalones: " << endl;
    cin >> n;

    cout << "Si se puede saltar de a un o de a dos escalones existen " << maneras(n) << " maneras de subir la escalera" << endl;

    return 0;

}


int maneras( int n )
{
    
    if( n == 0)
    {
        return 0;
    }
    else
    {

        int anterior = 0;
        int actual = 1;
        int tmp = 0;

        for( int i = 0; i < n ; ++i )
        {

            tmp = actual;
            actual = actual + anterior;
            anterior = tmp;

        }

        return actual;

    }

}