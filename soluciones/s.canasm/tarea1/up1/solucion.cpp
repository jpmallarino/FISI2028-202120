// "Universidad de los Andes - Tarea 1 - Metodos Computacionales - La Escalera" 
// "Samuel David Cañas Molina 201922001" 

//Parte a 
#include <string>
#include <iostream>


using namespace std;


int NumeroPosibilidades(int n){

    if ( n == 0 )
        return 1;
    else if ( n == 1  || n == 2 )   
        return n;
    return NumeroPosibilidades(n-1) + NumeroPosibilidades(n-2);

}

int main(){

    int n;
    cout << "Ingrese la cantidad de escalones" << endl;
    cin>>n;
    cout<< "El numero total de posibilidades es: "<< NumeroPosibilidades(n) << endl;
    
    return 0;
}

