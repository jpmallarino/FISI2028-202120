#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    
    int escalones;
    int nusaltos;
    int contador = 0;
    
    cout << "Número de escalones: "; 
    cin >> escalones;
    cout << "Número de saltos: "; 
    cin >> nusaltos;
    
    escalones = escalones - 1; //Para contarlos desde 0
    
    int escalera[escalones];
    int saltos[nusaltos];
    
    if (nusaltos >= 1)
    {
        cout << "De a cuantos escalones desea saltar: ";
    
        for (int i= 0; i<nusaltos; i++)
        {
            int i_temp;
            cin >> i_temp;
            saltos[i] = i_temp;

            if (saltos[i] == saltos[i-1])
            {
                cout<< "Introduzca un salto diferente: ";
                cin >> i_temp;
            }
        }
    }
    else 
    {
        cout << "Imposible subir la escalera" << endl;
    }

    
    if (escalones > 0 && nusaltos == 1)
    {
        cout << "Solo hay 1 forma de subir la escalera"<< endl;
        return 0;
    }
    
    
    if (escalones > 0 && nusaltos == 2) //Secuencia Fibonacci
    {
        
        int ii,x=0,y=1,z=1;
        
        for (ii = 1; ii <= escalones; ii++)
        {
            z = x+y;
            x = y;
            y = z;
        }
        
        cout << "Existen " << z << " formas de subir la escalera." << endl;
        return 0;
    }
    
    for (int i= 0; i<nusaltos; i++)  //Me ordena el vector
    {
        for(int j=i+1;j<nusaltos;j++)
        {
            if (saltos[i]>saltos[j])
            {
                int temp_1 = saltos[i];
                saltos[i]=saltos[j];
                saltos[j] = temp_1;
            }
        } 
        //cout<< saltos [i] <<endl;
    }
    

    for (int i = 0; i<escalera[escalones]; i++) // Me pone los escalones en 0
    {
        escalera[i] = 0;
        cout<< "Escalones: "<<escalera[i] <<endl;
    }
    
    
    int salto_1 = saltos[0];
    escalera[1] = salto_1;
    
    for (int j=0
   
    cout << "Escalon 0: " << escalera[1] << endl;
    
        
    
    cout<< "Contador: " << contador<< endl;

    

    //cout << "Contador " << contador << endl;

    

    //for (i = 1; i <= escalones; i+=2)
    //{
    //  *escalera = i;
    //escalera [i] = 2;
    //cout << "Valor " << i << " = " << escalera[i] << endl;
    //}

    //contador ++;
    
    //https://es.wikipedia.org/wiki/Anexo:Operadores_de_C_y_C%2B%2B



    // crear un programa que me lee un numero determinado de entradas
    //int entradas = 10;
    //int vals[10]; // crea un vector de 10 componentes en memoria de MAIN
    // esto es una declaracion estatica

    //int *vals2 = nullptr; // crea un apuntador a memoria vals2

    //vals2 = new int[1000]; // me devuelve una direccion de memoria con 1000 enteros reservados!

    //cout << "el numero de entradas es: "<<entradas<<endl;
    //int i = 0;
    //for (i = 0; i < entradas; i++){
    // //cout<<"ingrese entrada "<<i+1 << " " ;cin >> vals2[i];
    //}

    //cout << vals2[0] << ", ";
    //cout << vals2[9] << endl;

    //cout << "un elemento extrano " << vals2[999] << endl;

    //delete [] vals2; vals2 = nullptr; // Segmentation Fault!
    //delete [] escalera; escalera = nullptr;
    
    return 0;
    
}    