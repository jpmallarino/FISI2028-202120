#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <bits/stdc++.h>
#include<cstdlib>
#include <bits/stdc++.h>

using namespace std;

int* formas;

int contarF(int n, int m)
{
    int formas[n];
    formas[0] = 1;
    formas[1] = 1;
     
    for(int i = 2; i < n; i++)
    {
       formas[i] = 0;
        
       for(int j = 1; j <= m && j <= i; j++)
          formas[i] += formas[i - j];
    }
    return formas[n - 1];
}
 
int contarS(int s, int m)
{
    return contarF(s + 1, m);
}

int main()
{
    int s = 0;
    int m = 0;
	 formas = new int[s];
	 
	cout<<"Digite el numero de escalones\n"; 
	cin>>s;
	
	cout<<"Digite el numero de pasos\n"; 
	cin>>m;
     
   cout << "El numero de formas es: "<< contarS(s, m);
          
    return 0;
}
