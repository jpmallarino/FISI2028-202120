#include <iostream>
#include<fstream>

 
/*using Eigen::MatrixXd;
using namespace Eigen;*/
using namespace std;



void leermatriz(string fileName){

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL)
        exit(EXIT_FAILURE);

    char renglon[80];

    fgets(renglon, 79, fp);
    char *token = strtok(renglon, " ");
    int filas = atoi(token);
    token = strtok(NULL, " ");
    int columnas = atoi(token);
    int **matriz = new int*[filas];
    for (int i = 0; i<0 ; i=i+1){
        matriz[i] = new int[columnas];
        fgets(renglon, 79, fp);
        token =strtok(renglon, " ");
        matriz[i][0] = atoi(token);
        for (int j = 0; j<columnas ; j=j+1){
            token = strtok(NULL, " ");
            matriz[i][j] = atoi(token);
        } 
    }

    fclose(fp);
    return matriz;
}




void inver_gaussJ(){

    int i, j, k, Identidad[sizeof(matriz)/sizeof(*matriz)][sizeof(matriz)/sizeof(*matriz)], Inversa[sizeof(matriz)/sizeof(*matriz)][sizeof(matriz)/sizeof(*matriz)];

    float auxiliar, apoyo;

    for (i=0; i<sizeof(matriz)/sizeof(*matriz) ; i=i+1){
        for (j=0; j<sizeof(matriz)/sizeof(*matriz) ; j=j+1){
            
            if (i==j)
                Identidad[i][j] = 1;
            else
                Identidad[i][j] = 0;

        }
    }


    for (i=0; i<sizeof(matriz)/sizeof(*matriz) ; i=i+1){
        for (j=0; j<sizeof(matriz)/sizeof(*matriz) ; j=j+1){
               
            cout<<Identidad[i][j]<<"  \n";

        }
        cout<<endl;
    }



    for (i=0; i<sizeof(matriz)/sizeof(*matriz) ; i=i+1){

        apoyo = matriz[i][i];
        for (k=0; k<sizeof(matriz)/sizeof(*matriz) ; k=k+1){

            matriz[i][k] = matriz[i][k] / apoyo; 
            Identidad[i][k] = Identidad[i][k] / apoyo;


        }

        for (j=0; j<sizeof(matriz)/sizeof(*matriz) ; j=j+1){

            if (i!=j)
                auxiliar = matriz[j][i];

            for (k=0; k<sizeof(matriz)/sizeof(*matriz) ; k=k+1){

                matriz[j][k] = matriz[j][k] - auxiliar * matriz[i][k];
                Identidad[j][k] = Identidad[j][k] - auxiliar * Identidad[i][k];
            }
        }


    }

    Inversa = Identidad;
    return Inversa;
}



    //void inver_cofac(){




    //}




int main(){


    int matriz[i][j], GJ[i][j];

    string archivo;

    cout<< "Hola, usuario. Este programa sirve para invertir matrices nxn. \n";
    cout<<"Escribe el archivo  .txt  que deseas abrir, donde solo se encuentre la matriz. \n";
    cin>>matriz=leermatriz(archivo)>>endl;  // ir guardando en cada valor de la matriz[i][j] los valores con la función  *leermatriz*
    cout<<"La matriz es:  \n";
    cout<<matriz <<endl;

    // generar matriz identidad nxn 






    cout<< "La matriz inversa por el método Gauss-Jordan es:  \n";
    GJ=inver_gaussJ();
    cout<<GJ<<endl;
    //imprimir GJ en archivo txt
    cout<<endl;


    /*cout<< "La matriz inversa por el m[etodo de reducción por cofactores es:  \n";
    COF=// invertir matriz por cofactores;
    cout<<COF<<endln;
    // imprimir COF en archivo txt
    cout<<endln;
    
    cout<< "Utilizando la libreria de Eigen, la matriz inversa es:  \n";
    Eigen_ = // invertir matriz utilizando libreria Eigen;
    cout<<Eigen_<<endln;
    // imprimir Eigen_ en archivo txt;*/





    return 0; 
}







//   Profe, sugiero hacer algo con la sección. Estamos la mayoría muriendo con este curso.
// Profe, le envío lo que llevo (tal vez en lo que resta de dias logre armar el rompecabezas que tengo)





