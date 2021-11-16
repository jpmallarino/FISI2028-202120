// Tarea 1 : La Escalera


#include <iostream>
#include <string>

using namespace std;



// https://www.youtube.com/watch?v=0zvG6bIZ5KY&ab_channel=ApnaCollege
// min 5:32 (ver video hindú)



int posibilidades(int escalones){

    if ( escalones == 0 )
        return 1;
    
    else if ( escalones == 1  || escalones == 2 )   
        return escalones;
    
    return posibilidades(escalones-1) + posibilidades(escalones-2); //  sumar N sumandos  posibilidades(escalones-Valor_paso)

}


// No se como se hace la generalizacion 



int main(){

    int escalones;
    cout << "Escribe la cantidad de escalones" << endl;
    cin>>escalones;
    cout<< "las posibilidades son: "<< posibilidades(escalones) << endl;
    





    return 0;
}
















