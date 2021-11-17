#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <bits/stdc++.h>
#include<cstdlib>

using namespace std;

//Vectoresdinámicos 
int *punteroN;
int *punteroJ;
int *punteroM;

int paradaM = 0;
int n = 0;
int j = 0;
int m = 0;
int s = 0; 


int posib(int n, int j){
	
	punteroN[0] = 1;
	int contador = 0;
	
	for (int i = 1; i <= n; i++){
		
		int k = i - j - 1;
		
      int k2 = i - 1;

      if (k >= 0)
      {
         contador -= punteroN[k];
      }
      contador += punteroN[k2];
		punteroN[i] = contador;	
    }
	return punteroN[n];
}

int parada(int n, int j, int m){

	punteroM[0] = 1;
	int contadorM = 0;
	
	for (int i = 1; i <= m; i++){
		int K = i - j - 1;
		int K2 = i - 1;
		if (K >= 0)
		{
			contadorM -= punteroM[K];
		}
		contadorM += punteroM[K2];
		punteroM[i] = contadorM;
		
	}
	return punteroM[m];
	}
	
int paradaEnM(void){
	
	if(s <= j && s > 0 && j < n){
		
		return posib(n-m, j)*parada(n, j, m);
	}
}

int mul(int n, int m){

	punteroJ[0] = 1;
	
	for (int i = 1; i <= n; i++){
		int contador = 0;
		for (int j = 1; j <= m ; j++){
			 if (i-j >= 0){
					contador = parada(n-m, j, m)*posib(n, j);
			 }
      }
		punteroJ[i] = contador;	
		
    }
	return punteroJ[n];
	}


int main(void){
	
	punteroN = new int[n];
	punteroJ = new int[n+1];
   punteroM = new int[m];
	
	cout<<"Digite el numero de escalones n es:\n"; 
	cin>>n;
	
	cout<<"Digite el numero de pasos j:\n"; 
	cin>>j;
	
	cout<<"Digite del escalin m en donde quiere la parada obligada:\n"; 
	cin>>s;	
	
	cout<<"Digite el numero de paradas obligadas es:\n"; 
	cin>>m;	
	
	
	if(j > 0 && n > 0 && j <= n && m < n){
		//Punto a y b
		cout <<"RESPUESTA:"<<endl;
		
		cout << "El numero de formas posibles para subir"<<" "<<n<<" "<<"escalones con"<<" "<<j<<" "<<"pasos es:\n"<< posib(n, j)<<endl;

		cout<<"El numero de posibilidades con la parada obliogada en el escalon"<<" "<<m<<" "<<"es:\n"<<paradaEnM()<<endl;

		cout<<"El numero de posibilidades con"<<" "<<m<<" "<<"paradas obligadas es:\n"<<mul(n, m)<<endl;
	}
	else{
		cout<<"El numero de pasos debe ser menor o igual al numero de escalones y ambos diferentes de cero.\nAdemas, el numero  de paradas debe ser menor a el numero de escalones."<<endl;
		cout<<"Por favor cierre y digite nuevamente.";
	}

   delete[] punteroN;
	delete[] punteroJ; 
   delete[] punteroM;
   
   return 0;
}
