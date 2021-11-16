#include <iostream>
#include<stdlib.h>
using namespace std;

//Prototipo de Función
int cantidadSaltos(int n, int nSaltos, int saltos[]);

//Función Principal
int main() 
{

    //Declaramos las variables
    int nEscalas, nSaltos, nParadas, cantidad, repite, organize;
    //Declaramos los punteros
    int* saltos, * paradas;

    //Pedimos la cantidad de escalones y posibles saltos
    cout<<"¿Cuantos escalones hay? ";cin>>nEscalas;

    //Pedimos cuantas combinaciones de escalones podra subir
    cout<<"¿Cuantas condiciones de escalones desea aniadir? ";cin>>nSaltos;

    //Pedimos de a cuantos escalones podra subir, puede ser mas de uno
    cout<<"¿De a cuantos escalones desea subir? ";
    saltos=new int[nSaltos];
    for(int i=0;i<nSaltos;++i) 
    {
        cout<<"De a ";cin>>saltos[i];
    }

    //Pedimos cuantas paridas obligatorias va a tener, puede ser mas de una
    cout<<"¿Cuantas palabras obligatorias desea poner? ";cin>>nParadas;
    if(nParadas>0)//Si no tiene paradas, corre sin restriccion
    {
        //Pedimos donde van a estar ubicadas las paradas
        cout<<"En que escalon desea las paradas? ";
        paradas=new int[nParadas];
        for(int i=0;i<nParadas;++i) 
        {
            cout<<"En el ";cin>>paradas[i];
        }

        //Ahora vamos a ordenar
        for(int i=0;i<nParadas;i++) 
        {
            for(int j=0;j<nParadas-1;j++) 
            {
                if(*(paradas+j)>*(paradas+1+j)) 
                {
                    organize=*(paradas+j);
                    *(paradas+j)=*(paradas+1+j);
                    *(paradas+j+1)=organize;
                }
            }
        }
        //Se calcula la cantidad de formas de subir
        for(int i=0;i<nParadas;++i) 
        {
            if(i==0)
            {
                cantidad=cantidadSaltos(paradas[i]+1,nSaltos,saltos);
            }
            else 
            {
                cantidad*=cantidadSaltos(paradas[i]-paradas[i-1],nSaltos,saltos);
            }
            repite = cantidadSaltos(nEscalas-paradas[nParadas-1]+1,nSaltos,saltos);
        }
        cout<<"Hay "<<cantidad*repite<<" formas de subir la escalera segun las condiciones dadas."<<endl;
    }
    else
    {
        cantidad = cantidadSaltos(nEscalas, nSaltos, saltos);
        cout<<"Hay "<<cantidad<<" formas de subir la escalera segun las condiciones dadas."<<endl;

    }
    return 0;
}

//Funcion que devuelve cantidad de saltos segun 3 parametros, cantidad de escalones, cantidad de saltos y saltos permitidos
int cantidadSaltos(int n, int nSaltos, int saltos[]) {
    int cantidades=0;
    if(n<0)
    {
        return 0;
    }
    else if (n==0||n==1) 
    {
        return n;
    }
    else 
    {
        for (int i=0;i<nSaltos;++i) 
        {
            cantidades+=cantidadSaltos(n-saltos[i],nSaltos,saltos);
        }
        return cantidades;
    }
}