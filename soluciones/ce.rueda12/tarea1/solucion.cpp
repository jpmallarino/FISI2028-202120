#include <iostream>
using namespace std;


int contador(int n, int m, int k)
{	
	int res[n];
	res[0] = 1;
	res[1] = 1;
	res[2] = 1; 
	
	
	for(int i = 2; i < n; i++)
	{
	res[i] = 0;
		
	for(int j = 1; j <= m && j <= i; j++)
		res[i] += res[i - j];
	
	for (int r = 0; r <= k && r >= i; r++ )
	    res[i] += res[i + r];
	}
	return res[n - 1];
}

int contadorFormas(int s, int m, int k)
{
	return contador(s + 1, m, k);
}

int main()
{
	int i,s,m,k,t=10;
	for(i=0;i<t;i++)
	{	cout<<"Ingrese el numero de escaleras n: ";
		cin>>s;
		cout<<"Ingrese el numero de escalones maximos que puede saltar m: ";
		cin>>m;
		cout<<"Ingrese el numero de paradas obligadas k: ";
		cin>>k; 
		cout<<" El numero de formas de subir la escalera es de: "<<contador(s+1,m,k)<<endl;
	}
	return 0;
}

