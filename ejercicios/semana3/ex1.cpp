#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void){
    // What about text?
    string BUFFER2;
    // cout<<"Capture line -> "; getline(cin,BUFFER2);
    // cout<<"Captured line:\n\t"<<BUFFER2<<endl;
    // cout<<"El primer caracter: '"<<BUFFER2[0]<<"'"<<endl;
    // cout<<"El primer caracter: '"<<BUFFER2[4]<<"'"<<endl;
    // cout<<"Longitud de caracteres: '"<<BUFFER2.length()<<"'"<<endl;

    // archivos
    ifstream entrada;
    ofstream salida;

    entrada.open("datasets/numbers.txt");

    while(getline(entrada,BUFFER2)){
        cout<<"linea: "<<BUFFER2<<endl; // como guardar?
    }

    salida.open("output.txt");

    salida<<"escribimos por primera vez"<<endl;

    // cerrar
    entrada.close();
    salida.close();
    return 0;
}
