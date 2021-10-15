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
    
    int maneras = 0;

    for(int i = 0; i<=n; ++i)
    {

        for( int j = 0; j<=n; ++j)
        {

            if( (i + 2*j) == n )
            {

                ++maneras;

            }

        }

    }

    return maneras;

}