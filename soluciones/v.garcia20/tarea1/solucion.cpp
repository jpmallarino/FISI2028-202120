// Tarea1
// Valentina Garcia Morales; 201912546
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>  

using namespace std;


int antes(int n, int cantidadP, int steps[])
{

	int contador = 0;

	if (n == 0 || n == 1)
	{
		return n;
	}
	else if (n < 0)
	{
		return 0; 
	}


	else
	{
		for (int i = 0; i < cantidadP; i++)
		{
			contador += antes(n - steps[i], cantidadP, steps);

		}
		return contador;
	}

}


void crearorden(int nparadas, int* parada)
{
	int var;
	for (int i = 0; i < nparadas; i++)
	{
		for (int j = 0; j < nparadas - 1; j++)
		{
			if (*(parada + j) > *(parada + j + 1))
			{
				var = *(parada + j);
				*(parada + j) = *(parada + j + 1);
				*(parada + j + 1) = var;
			}
		}
	}

}


int main()
{
	int escalones;
	int npasos;
	int nparadas;
	int* steps;
	int* parada;
	int posibilidades;
	int count;
	int posibilidadfinal;



	cout << "Ingrese la cantidad de los escalones ";
	cin >> escalones;

	cout << "Ingrese la cantidad de diferentes pasos ";
	cin >> npasos;

	steps = new int[npasos];

	for (int i = 0; i < npasos; i++)
	{
		
		cout << "Ingrese dichos pasos ";
		cin >> steps[i]; 

	}

	cout << "Ingrese cuántas paradas de descanso son ";
	cin >> nparadas;

	parada = new int[nparadas];

	for (int i = 0; i < nparadas; i++)
	{
		cout << "Ingrese en orden las paradas ";
		cin >> parada[i];
	}

	crearorden(nparadas, parada);

	if (nparadas <= 0)
	{
		posibilidades = antes(escalones, npasos, steps);

	}

	else
	{
		count = 0;

		for (int i = 0; i < nparadas; i++)
		{
			if (i != 0)
			{
				posibilidades = antes(parada[i] - parada[i - 1] + 1, npasos, steps);
				
			}
			else
			{
				posibilidades = antes(parada[i] + 1, npasos, steps);
			}

		}
		posibilidades = antes(escalones - parada[nparadas - 1] + 1, npasos, steps);

		if (nparadas > 1)
		{
			posibilidades = posibilidades;

		}

		
	}

	cout << "Las posibles formas de subir la escalera son: " << posibilidades << "\n";



}




