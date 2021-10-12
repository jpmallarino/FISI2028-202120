// Your First C++ Program

#include <iostream>
#include <vector> 

//Declaracion de funciones
//Funcion (a)
int escalera(int n);
//Funcion (b)
int escalerab(int Pn, int P);
int contarEscalera2(int s, int P);
//Funcion (b)
int escalerabconpaso(int Pn, int P, int m);
int contarEscalera3(int s, int P,int m);




int main() {
    std::cout << "Hello Martin, " <<  std::endl;
    
    //Variable entrada punto a
    int n = 6;

    //Variable entrada punto b
    int m = 3;

//Variable entrada punto c


    //Declaracion lista punto b

    std::vector<int> lista (4);
    

    int ret;
    int retPRO;
    
    

    lista = { 4, 5, 6, 7, 8 };
    
    int s = 6;
    int P = 2;

 
    // Funcion escalera punto a
    ret = escalera(n);
    std::cout << "El numero de posibilidades para "<< n << " escaleras  con pasos de (1,2) es : " << ret <<  std::endl;

    // Funcion escalera punto b mejorada
    retPRO = contarEscalera2(s, P);
    std::cout << "El numero de posibilidades para "<< s << " escaleras con el conjunto de " << P << " numeros dado es : " << retPRO <<  std::endl;

    return 0;
}

// Punto (a)

int escalera(int n)
{
    if (n==1 || n==0)
        return 1;
    else if (n==2)
        return 2;
    else
        return escalera(n-2) + escalera(n-1);
}



//Punto b



int escalerab(int Pn, int P)
{
    if (Pn <= 1)
    {
        return Pn;
    }
     
    int res = 0;
    for(int i = 1; i <= P && i <= Pn; i++)
    {
       res += escalerab(Pn - i, P);
    }
    return res;
}

int contarEscalera2(int s, int P)
{
    return escalerab(s + 1, P);
}
 



// Punto (c)




int escalerabconparo(int Pn, int P, int m)
{
    if (Pn <= 1)
    {
        return Pn;
    }
     
    int res = 0;
    for(int i = 1; i <= P && i <= m; i++)
    {
       res += escalerab(m - i, P);
    }
    
    for(int i = 1; i <= P && i <= Pn-m; i++)
    {
       res += escalerab(Pn -m- i, P);
    }

    return res;
}

int contarEscalera3(int s, int P,int m)
{
    return escalerabconparo(s + 1, P,m);
}
 

 // Punto (d)