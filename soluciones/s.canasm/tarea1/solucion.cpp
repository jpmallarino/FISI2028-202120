// "Universidad de los Andes - Tarea 1 - Metodos Computacionales - La Escalera" 
// "Samuel David Cañas Molina 201922001" 


#include <string>
#include <iostream>
#include <vector>
#include <iterator> //borrar despues 
#include <cmath>

using namespace std;

//Parte a 

/*int NumeroPosibilidades(int n){

    if ( n == 0 )
        return 1;
    else if ( n == 1  || n == 2 )   
        return n;
    return NumeroPosibilidades(n-1) + NumeroPosibilidades(n-2);

}*/
template <typename T>
ostream& operator<<(ostream& o, const vector<T>& arr) {
copy(arr.cbegin(), arr.cend(), ostream_iterator<T>(o, " "));
return o;
}

vector<int> SiguienteTupla (vector<int> v, int m){

    v[0]+=1;
    int carry = 0;
    
    for (int i=0; i<v.size();i++){
        if (v[i]==m){
            v[i]=0;
            carry ++;
            if (i+1!=v.size()){
                v[i+1]++;
            }
            else {
                v.push_back(1);
            }
            
        }
        
    }
    return v;
}

int SumaEnIndices (vector<int> indices, vector<int> pasos){
    int suma=0;
    for (int i=0; i<indices.size();i++){
        suma+=pasos[indices[i]];
    }
    return suma;
}

int NumeroPosibilidades (int n, vector<int> pasos){
    vector<int> indices={0};
    int limite =1+ceil(n/(double)pasos[0]);
    int posibilidades =0;
    
    cout<<limite<<endl;
    
    while (indices.size()<limite){
        cout<<indices<<endl;
        if (SumaEnIndices(indices, pasos)==n){
            posibilidades++;
        }
        indices=SiguienteTupla(indices,pasos.size());
    }
    return posibilidades;
}


int main(){

    int n;
    /*cout << "Ingrese la cantidad de escalones" << endl;
    cin>>n;
    cout<< "El numero total de posibilidades es: "<< NumeroPosibilidades(n) << endl;*/
    vector<int> prueba = {1,2,0};
    cout<<NumeroPosibilidades(4, prueba);
}
