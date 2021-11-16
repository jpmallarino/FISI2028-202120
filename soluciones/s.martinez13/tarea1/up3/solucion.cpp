#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    
    int escalones;
    int nusaltos;
    int nuparadas;
    int contador = 0;
    
    cout << "Número de escalones: "; 
    cin >> escalones;
    cout << "Número de saltos: "; 
    cin >> nusaltos;
    
   // escalones = escalones - 1; //Para contarlos desde 0
    
    int escalera[escalones] = {};
    int saltos[nusaltos];
    
    if (nusaltos >= 1) //Saltos
    {
        cout << "¿De a cuántos escalones desea saltar? ";
    
        for (int i= 0; i<nusaltos; i++)
        {
            int i_temp;
            cin >> i_temp;
            saltos[i] = i_temp;
            
            if (saltos[i] > escalones)
            {
                cout<< "Introduzca un salto menor al número de escalones: ";
                cin >> i_temp;
            }
        }
        
        for (int i= 0; i<nusaltos; i++)
        {
            int saltocorregido;
            
            for (int j= 0; j<nusaltos; j++)
            {
                if (i != j && saltos[i] == saltos[j])
                {
                    cout<< "Introduzca un salto diferente a los ya introducidos: ";
                    cin >> saltocorregido;
                    saltos[i] = saltocorregido;
                }
            }
        }
    }
    else 
    {
        cout << "Imposible subir la escalera" << endl;
    }

    cout << "Número de paradas: "; 
    cin >> nuparadas;
    int paradas[nuparadas];
    
      
    if (nuparadas >= 1) //Paradas
    {
        cout << "¿En qué posiciones desea parar? ";
    
        for (int k= 0; k<nuparadas; k++)
        {
            int i_temp_2;
            cin >> i_temp_2;
            paradas[k] = i_temp_2;
            
            if (paradas[k] > escalones)
            {
                cout<< "Introduzca una parada menor al número de escalones: ";
                cin >> i_temp_2;
            }
            
        }
        
        for (int k= 0; k<nuparadas; k++)
        {
            int paradacorregida;
            
            for (int l= 0; l<nuparadas; l++)
            {
                if (k != l && paradas[k] == paradas[l])
                {
                    cout<< "Introduzca una parada diferente a las ya introducidas: ";
                    cin >> paradacorregida;
                    paradas[k] = paradacorregida;
                }
            }
        }
    }
    
  
    if (escalones > 0 && nusaltos == 1)
    {
        cout << "Solo hay 1 forma de subir la escalera"<< endl;
        return 0;
    }

    
    for (int i= 0; i<nusaltos; i++)  //Me ordena el vector de saltos
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
    
    for (int i= 0; i<nuparadas; i++)  //Me ordena el vector de paradas
    {
        for(int j=i+1;j<nuparadas;j++)
        {
            if (paradas[i]>paradas[j])
            {
                int temp_1 = paradas[i];
                paradas[i]=paradas[j];
                paradas[j] = temp_1;
            }
        } 
        //cout<< saltos [i] <<endl;
    }
    
    int Pos_temp = 0;
    
    for (int i=0; i<nusaltos; i++) //Inicializa los primeros saltos de arriba hacia abajo 
    {
        Pos_temp = escalones - saltos[i];
        escalera[Pos_temp] = 1;
        //cout<< "Escalon " << Pos_temp << ": " << escalera[Pos_temp] <<endl;
    }
    
    int escalon_n = 0;
    
    for (int j=1; j<=escalones; j++)
    {
        escalon_n = escalones - j;
        int Valor_temp = 0;
        
        for (int i=0; i<nusaltos; i++)  
        {
             if((escalon_n + saltos[i])< escalones) //No cima no datos inic
             {
                 Valor_temp += escalera[escalon_n + saltos[i]];
                 escalera[escalon_n] = Valor_temp;
             }
        }
    }
    
    
    
    if (nuparadas == 0)
    {
        cout << "Existen " << escalera[0] << " formas de subir la escalera" << endl;
        return 0;
    }
    else 
    {
        int parada0 = escalones - paradas[0];
        int escaleraconparadas = escalera[parada0];

        for (int i = 1; i<nuparadas; i++)
        {
            int parada_i = paradas[i+1] - paradas[i];
            escaleraconparadas *= escalera[parada_i];
            //escaleraconparadas *= escalones[parada_i];
        }

        cout << "Existen " << escaleraconparadas << " formas de subir la escalera" << endl;

    }
    
    
    
    //Mostrar los valores del arreglo:
    
    //for (int i=0; i<escalones; i++)  
    //{
    //    cout<< "Escalon " << i << ": " << escalera[i] <<endl;
    //}
    
    
    return 0;
    
}    