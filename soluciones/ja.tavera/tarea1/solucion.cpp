#include<iostream>
#include<fstream>


using namespace std;
int maneras(int n, int *p, int j) {
	
	if (n < 0)
	{
		return 0;
	}
	if (n == 0)
	{
		return 1;
	}
	
	
	int m = 0;
		
	for (int i = 0; i < j; i++)
	{
		m += maneras( n - p[i], p, j);	
	}
	return m;
	
	
}
int maneras_con_pasos(int n, int m, int *q, int *p, int j)
{
	if (0<m < n)
	{	
		
		int x = 1;
		for (int i = 0; i < m; i++)
		{
			if (i + 1 < m)
			{
				x = x * maneras(q[i + 1] - q[i], p, j);
			}

		}
		return x * maneras(q[0], p, j) * maneras(n - q[m - 1],p,j);

	}
	else
	{
		return 0;
	}
}	

int main(){
	int n = 0; //Que pena profe por no poner los nombres de las variables en el pdf (n,i,p,j,m) exactamente a lo que corresponden en este
	int j = 0; //ejercicio, lo que pasa es que poner i como nombre de variable me confunde a la hora de iterar ya que siempre lo hago con
	int m = 0;//esa letra. De resto funciona bien.
	
	
	cout <<"Ingrese el numero de escalones: "; cin >> n;
	cout << "Ingrese la cantidad de posibles saltos: "; cin >> j;
	cout << "Ingrese la cantidad de pasos obligatorios: "; cin >> m;
	int *escalones = nullptr;
	int *obligatorios = nullptr;
	escalones = new int[j];
	obligatorios = new int[m];
	for(int i = 0; i < j; i++)
	{
		cout << "Ingrese posible salto " << i+1 <<": "; cin >> escalones[i];
		
	}
	for (int i = 0; i < m; i++)
	{
		cout << "Ingrese escalon obligatorio " << i + 1 << ": "; cin >> obligatorios[i];

	}

	cout << "El numero de formas posibles es: " << maneras(n, escalones, j) << endl;
	cout << "El numero de formas posibles con los pasos obligatorios dados son: " << maneras_con_pasos(n,m, obligatorios, escalones, j)<<endl;
	




	delete [] escalones; escalones = nullptr;
	delete [] obligatorios; obligatorios = nullptr;
	return 0;
}