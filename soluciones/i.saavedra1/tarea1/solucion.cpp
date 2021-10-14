//
//  main.cpp
//  TareaLaEscalera
//
//  Created by Isabella  Saavedra Morales on 6/09/21.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
int escala=0;
int stair=0;
int *stairs;
int stop;
int stops;

//Punto a
int Escalera1o2(int Escalones){
    if (Escalones <= 1)
        {
            return Escalones;
        }
         
        int respuesta = 0;
        for(int i = 1; i <= 2 && i <= Escalones; i++)
        {
           respuesta += Escalera1o2(Escalones-i);
        }
        return respuesta;
}
int Escalera1o2Pt2(int n){

    return Escalera1o2(n+1);
    //retorna el numero de maneras de subir usando 1 o 2 escalones.
}


//Punto b
int fib(int n){
    stairs = new int [n];
    stairs[0]=1;
    stairs[1]=1;
    for (int i =1; i<=n;i++){
        stair = stairs[i-1]+stairs[i] ;
        stairs[i+1]=stair;
        
    }
    
    return stairs[n];//Retorna el numero de fibonacci n
    
}
//Retorna las maneras para subir una escalera de n escalones
int ways2(int n){
    if (n==1){
        return 1;
    }
    if (n==2){
        return 2;
    }
    else{
        return fib(n+1);
    }
}

//Punto c

//hace una sola parada en la mitad de la escalera.

int RestStop(int n){
    
    stop=n/2;
    
        return ways2(stop)+ways2(stop);
}

//hace paradas cada dos escalones hasta n y en caso de que sea un numero impar agrega un escalon mas.

int variousStops(int n){
    
    return ((n/2)*ways2(2))+((n%2)*ways2(1));
    
    
}


int main() {
    
    cout<<Escalera1o2(10)<<endl;
    cout<<" "<<endl;
    cout<<Escalera1o2Pt2(10)<<endl;
    cout<<" "<<endl;
    cout<< fib(10)<<endl;
    cout<<" "<<endl;
    cout<< ways2(10)<<endl;
    cout<<" "<<endl;
    cout<< RestStop(10)<<endl;
    cout<<" "<<endl;
    cout<<variousStops(10)<<endl;
    
    
    
    return 0;
}
