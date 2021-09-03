#include <iostream>
#include <fstream>
#include <string>
// Solucion 2: crear streams a partir de strings
#include <sstream>

using namespace std;

// namespace fisi2028 {
//     ? mean(?){
//     }

//     ? variance(?){
//     }
// }


//     char cstr[s.size() + 1];
//     strcpy(cstr, s.c_str());



int main(void){
    // What about text?
    string BUFFER2;

    string nom_archivo;
    cout << "Nombre del archivo de datos: ";
    cin >> nom_archivo;

    // archivos
    ifstream entrada;
    int entrada_num_lines = 0;

    entrada.open(nom_archivo);
    if(!entrada.is_open()){
        cerr << "Error abriendo archivo de datos " << nom_archivo << endl;
        exit(1);
    }

    while(getline(entrada,BUFFER2)){
        entrada_num_lines++;
    }
    cout << "El archivo " << nom_archivo;
    cout << " tiene " << entrada_num_lines << " lineas." << endl;

    // Debemos ir de nuevo al inicio del archivo!
    entrada.clear(); // elimina la bandera "fail"
    entrada.seekg(0); // vuelve al punto "cero"

    double x,y;
    int i = 0;

    // Solution 1: Copiemos cada entrada directamente usando streams!
    while( entrada >> x && entrada >> y ){
        i++;
        cout<<i<<": x="<<x<<" / y="<<y<<endl;
        // El problema es que si una linea tiene 3 elementos... jodidos!
    }

    // Solution 2: https://www.cplusplus.com/reference/string/stod/
    entrada.clear(); // elimina la bandera "fail"
    entrada.seekg(0); // vuelve al punto "cero"
    i = 0;
    string::size_type sz; // almacena la posicion donde termina el primero y comienza el segundo
    while(getline(entrada,BUFFER2)){
        x = stod (BUFFER2,&sz);
        y = stod (BUFFER2.substr(sz));
        i++;
        cout<<i<<": x="<<x<<" / y="<<y<<endl;
    }

    // Solution 3: Usando streams! (Me gusta mas pero es al gusto de cada quien!)
    entrada.clear(); // elimina la bandera "fail"
    entrada.seekg(0); // vuelve al punto "cero"
    i = 0;
    stringstream ss;
    while(getline(entrada,BUFFER2)){
        ss.clear();
        ss << BUFFER2; // la verdad, le puedo pasar lo que quiera!
        ss >> x >> y;
        i++;
        cout<<i<<": x="<<x<<" / y="<<y<<endl;
    }

    ofstream salida;
    salida.open("output.txt");

    if(!salida.is_open()){
        cerr << "Error abriendo archivo de salida output.txt" << endl;
        exit(1);
    }

    salida<<"escribimos por primera vez"<<endl;

    // cerrar
    entrada.close();
    salida.close();
    return 0;
}
