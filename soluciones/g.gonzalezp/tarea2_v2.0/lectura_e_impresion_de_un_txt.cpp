// leer un archovo txt e imprimirlo
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>



using namespace std;

int filas = 0;
int columnas = 0;



void guardarmatriz(char *filename, double **matriz){


    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        exit(EXIT_FAILURE);
    }

    char linea[80];
    sprintf(linea, "%d %d\n", filas, columnas);
    fputs(linea, fp);
    for(int i=0; i<filas; i++){
        linea[0] = '\0';
        for(int j=0; j<columnas; j++){
            char buffer[10];
            sprintf(buffer, "%d ", matriz[i][j]);
            strcat(linea, buffer);
        }

        int len = strlen(linea);
        linea[len-1] = '\n';
        fputs(linea, fp);

    }

    fclose(fp);

}















double** escritura(int orden){
    ofstream archivo;
    string nombreArchivo; /*string frase*/
    int i, j, k;
    double A[orden][orden],  aux, pivote;
    double** I[orden][orden];

    cout<<"Por favor, escriba el nombre como usted quiere que se llame el archivo incluyendo la extencion .txt  \n";
    cin>>nombreArchivo;
    
    archivo.open(nombreArchivo.c_str(), ios::out); //Si el archovo no existe, el ios::out lo crea, y si ya existía, lo reemplaza

    if(archivo.fail()){
        cout<<"No se pudo abirir y reemplazar o crear el archivo de extesion .txt  \n";
        exit(1);
    }

    /*cout<<"\nEscriba el texto del archivo \n";
    getline(cin, frase);

    archivo<<frase;*/  //preguntar por que no funciona, el error esta en los espacios  (al primer espacio deja de escribir)

    /*
    cout<<"\nEmpieza a pedir los datos \n";
    
    for(i=0; i<orden; i++){
        for(j=0; j<orden; j++){
            cin>>A[i][j];
            I[i][j]=0; 

            if(i==j){
                I[i][j]=1;
            }
           
                    
        }
    }

    
    cout<<"\nMatriz identidad:  \n";

    for(int i=0; i<orden; i++){
        for(int j=0; j<orden; j++){
            cout<<I[i][j]<<endl;
        }
    }

    

    //reducción por renglones
    for(i=0; i<orden; i++){
        pivote = A[i][i];

        //Convertir el pivote en 1 y aplicar la operacion sobre toda la fila
        for(k=0; k<orden; k++){
            A[i][k] = A[i][k] / pivote;
            I[i][k] = I[i][k] / pivote;
        }
        // este segundo ciclo se va a encargar de convertir en 0 todo lo que hay debajo y encima del pivote
        for(j=0; j<orden; j++){
            if(i!=j){
                aux = A[j][i];

                for(k=0; k<orden; k++){
                    A[j][k] = A[j][k] - aux * A[i][k];
                    I[j][k] = I[j][k] - aux * I[i][k];
                }
            }
        }

    }

    cout<<"\nMatriz inversa:  \n";

    for(i=0; i<orden; i++){
        for(j=0; j<orden; j++){
            cout<<I[i][j]<<endl;
        }
    }

    cout<<I[0][0];*/

    for(int index=1; index<=orden ; index++){
        archivo<<"Hola, mundo. Mi nombre es Gabriel ☺ \n";
        //archivo<<**I;
    }
    
    
    archivo.close();

    return **I;
}













int lectura(string ruta){

    ifstream archivo;
    string texto;
    int orden = 0;


    archivo.open(ruta, ios::in); // en esta parte se abre el archivo unicamente en modo lectura
    
    if(archivo.fail()) {
        cout<<"No se pudo abrir o no se encuentra el archivo \n";
        exit(1);    
    }


    while(!archivo.eof()){  //mientras no sea el final del archivo
        orden = orden + 1;
        getline(archivo, texto);
        cout<<texto<<endl;

        
    }

    

    
    

    archivo.close(); //se debe cerrar el archivo  despues de leerlo
    return orden;
}












int main(){

    string ruta;
    int orden;

    cout<<endl;
    cout<<"Hola, ingresa el nombre o ruta completa del archivo .txt (incluyendo dicha extencion) donde se encuantra la matriz. \n";
    cin>>ruta;
    //cout<<endl;
    
    orden = lectura(ruta); //lee e imprime la matriz en terminal

    int i, j, k;
    double A[orden][orden], I[orden][orden], aux, pivote;


    cout<<"\nEmpieza a pedir los datos \n";
    
    for(i=0; i<orden; i++){
        for(j=0; j<orden; j++){
            cin>>A[i][j];
            I[i][j]=0; 

            if(i==j){
                I[i][j]=1;
            }
           
                    
        }
    }

    
    cout<<"\nMatriz identidad:  \n";

    for(int i=0; i<orden; i++){
        for(int j=0; j<orden; j++){
            cout<<I[i][j]<<endl;
        }
    }

    

    //reducción por renglones
    for(i=0; i<orden; i++){
        pivote = A[i][i];

        //Convertir el pivote en 1 y aplicar la operacion sobre toda la fila
        for(k=0; k<orden; k++){
            A[i][k] = A[i][k] / pivote;
            I[i][k] = I[i][k] / pivote;
        }
        // este segundo ciclo se va a encargar de convertir en 0 todo lo que hay debajo y encima del pivote
        for(j=0; j<orden; j++){
            if(i!=j){
                aux = A[j][i];

                for(k=0; k<orden; k++){
                    A[j][k] = A[j][k] - aux * A[i][k];
                    I[j][k] = I[j][k] - aux * I[i][k];
                }
            }
        }

    }

    cout<<"\nMatriz inversa:  \n";

    for(i=0; i<orden; i++){
        for(j=0; j<orden; j++){
            cout<<I[i][j]<<endl;
        }
    }

   
    double **M = escritura(orden);//crea un nuevo .txt y escribe en él la matriz que luego guarda en la misma carpeta donde se encuentra contenido el programa
    guardarmatriz("MAtriz_Final.txt", M);
    
    return 0;
}













