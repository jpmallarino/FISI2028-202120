#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // string stream
#include <cmath>

using namespace std;

// mean = E[x]
double calc_promedio(double *v, int n){
    double suma=0;
    for(int i=0; i<n; i++)
        suma += v[i];
    return suma/n;
}

// varianza = E[x^2] - E[x]^2
double calc_varianza(double *v, int n){
    double suma=0;
    for(int i=0; i<n; i++)
        suma += (v[i]*v[i]);
    double e_x2 = suma / n;
    double e_x = calc_promedio(v,n);
    return e_x2 - e_x*e_x;
}

double desv_estandar(double *v, int n){
    // "unbiased" -> poblacional
    return sqrt(n*calc_varianza(v,n)/(n-1));
}


int main(void){
    // What about text?
    string BUFFER2;

    // archivos
    ifstream entrada;
    ofstream salida;

    entrada.open("datasets/numbers.txt");

    // 1. recorrer el archivo y reconocer cuantas lineas tiene.
    int num_lineas = 0;
    while(getline(entrada,BUFFER2)){
        num_lineas ++ ;
    }
    cout<<"cuantas lineas tiene el archivo? "<<num_lineas<<endl;

    // Test conceptual
    float temp[5] = {0,-1,1,-2,2};
    cout << "la direccion de temp es: "<< temp << endl;
    // 2. dimensionar el vector: double
    double *x, *y;
    x = new double[num_lineas];
    y = new double[num_lineas];
    // 3. volvemos a recorrer el archivo y guardando los datos
    entrada.clear(); // elimina la bandera "fail"
    entrada.seekg(0); // vuelve al punto "cero"
    // 3.1 Manera mas interesante
    int i = 0;
    while(getline(entrada,BUFFER2)){
        stringstream ss(BUFFER2);
        ss >> x[i] >> y[i];
        i ++ ;
    }

    for(i=0;i < num_lineas; i++){
        cout << i+1 << "-> x=" << x[i] << " y=" << y[i] << endl;
    }
    // 4. hacer una funcion que me calcule el promedio y la varianza
    double promedio_x,varianza_x,desv_est_x;
    double promedio_y,varianza_y,desv_est_y;

    // TENGO QUE ENVIAR EL NUMERO DE ELEMENTOS!!!
    promedio_x = calc_promedio(x,num_lineas); // x es una direccion de memoria
    promedio_y = calc_promedio(y,num_lineas); // y es una direccion de memoria
    varianza_x = calc_varianza(x,num_lineas); // x es una direccion de memoria
    varianza_y = calc_varianza(y,num_lineas); // y es una direccion de memoria
    desv_est_x = desv_estandar(x,num_lineas); // x es una direccion de memoria
    desv_est_y = desv_estandar(y,num_lineas); // y es una direccion de memoria

    salida.open("output.txt");

    salida<<"escribimos por primera vez"<<endl;
    salida<<"x: "<<promedio_x<<" +/- "<<desv_est_x<<" [var(x)="<<varianza_x<<"]"<<endl;
    salida<<"y: "<<promedio_y<<" +/- "<<desv_est_y<<" [var(y)="<<varianza_y<<"]"<<endl;


    // cerrar
    entrada.close();
    salida.close();

    delete [] x; x = nullptr;
    delete [] y; y = nullptr;
    
    return 0;
}
