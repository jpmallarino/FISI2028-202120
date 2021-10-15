#include <iostream> 
using namespace std;

//Funcion de recursividad para encontrar el numero de escalones 

int fib(int n, int pasos,int *lista1){

int count = 0;
if(n<=1){
    return n;   
}

for(int i = 0; i<pasos; ++i){
    
 count += fib(n-lista1[i],pasos,lista1);   
    
}
 
  return count;
    
}

//Funcion que permite encontrar las manereas dependiendo de las paradas 

int Ways(int n, int pasos, int m, int *lista1, int *lista2){
    int result = 0;
  
   for (int i = 0; i < m; ++i) 
   {
        if(i == 0)
        {
            result = fib(lista2[i]+1, pasos, lista1);
        }
      
            result *= fib(lista2[i]-lista2[i-1], pasos, lista1);
    }
    
    
    return result;
    
    
    
}



int main()
{
  
  int n;
  int m;
  int pasos;
  int paradas;
  int *lista1;
  int *lista2;
  int result;
    
//Se ingresan los parametros por consola, por lo que es necesario hacer vectores dinamicos para esta parte    
    
  cout << "Cantidad de escalones" << endl;
  cin >> n;
    
  cout << "Cantidad de pasos" << endl;
  cin >> pasos;
    
  lista1 = new int[pasos];
  for(int i = 0; i<pasos; i++)
  {
      cout << "Ingrese los pasos["<<i<<"]: ";
      cin >> lista1[i];
      
  }
  
  cout << "Cantidad de Paradas" << endl;
  cin >> m;
  
  lista2 = new int[m];
  for(int i = 0; i<m; i++)
  {
      cout << "Ingrese las paradas["<<i<<"]: ";
      cin >> lista2[i];
      
  }
   
//Para hacer el Ordenamiento, se puede usar el metodo de la burbuja
    
    int sort_;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (*(lista2 + j) > *(lista2 + j + 1)) {
                sort_ = *(lista2 + j);
                *(lista2 + j) = *(lista2 + j + 1);
                *(lista2 + j + 1) = sort_;
            }
        }
    }
    
    int sort_2;
    for (int k = 0; k < m; k++) {
        for (int v = 0; v < m - 1; v++) {
            if (*(lista1 + v) > *(lista1+v+1)) {
                sort_2 = *(lista1+v);
                *(lista1+v) = *(lista1+v+1);
                *(lista1+v+1) = sort_2;
            }
        }
    }
    
   

    
  cout << "Las posibles formas son. "<< Ways(n,pasos,m,lista1,lista2);
    
  return 0;  
    
} 