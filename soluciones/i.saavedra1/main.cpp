//
//  main.cpp
//  eigen
//
//  Created by Isabella  Saavedra Morales on 6/10/21.
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fstream>
#include <cmath>


using namespace std;
float diagonal;
float NoDiagonal;
float diagonalInv;
float NoDiagInv;
float b;
float c;
float d;
float det;

int main() {
    //////////////////////////////////
    //Lee el archivo.
    //////////////////////////////////
    string myText[2];
    ifstream MyFile("2.txt");

    cout<<"Matriz del archivo:"<<endl;
    int n =0;
    while (getline(MyFile,myText[n]))
    {
        cout<<myText[n]<<endl;
        n=n+1;
    }
    MyFile.close();
    
    cout<<" "<<endl;
    cout<<"1.Gauss Jordan "<<endl;
    cout<<" "<<endl;
    //////////////////////////////////
    //Llena una matrix vacia con la del archivo.
    //////////////////////////////////
    float M[n][n];
    float N[n][n];

    for (int i=0;i<n;i++){
        int comas=0;
        for (int j =0;j<myText[i].size() ;j++){
            char miTexto=myText[i][j];

            //cout<<"Antes del if: "<<miTexto<<endl;
            // ESTO ENCUENTRA LAS COSAS EN RAW.
                if(miTexto!=','){
                    M[i][j-comas]=miTexto-'0';
                    // Cuando lo pasaba de char a int cogía un formato distinto entonces restandole cero da.
                    //   cout<<"Dentro del if: "<<M[j][i]<<endl;
                }
                else{
                    comas=comas+1;

                }
        }
    }
    for (int i=0;i<n;i++){
        int comas=0;
        for (int j =0;j<myText[i].size() ;j++){
            char miTexto=myText[i][j];

            //cout<<"Antes del if: "<<miTexto<<endl;
            // ESTO ENCUENTRA LAS COSAS EN RAW.
                if(miTexto!=','){
                    N[i][j-comas]=miTexto-'0';
                    // Cuando lo pasaba de char a int cogía un formato distinto entonces restandole cero da.
                    //   cout<<"Dentro del if: "<<M[j][i]<<endl;
                }
                else{
                    comas=comas+1;

                }
        }
    }
    
    //////////////////////////////////
    //Crea matriz identidad
    //////////////////////////////////
    
    float I[n][n];
    for( int i =0; i<n ; i++)
    {
      for( int j=0; j<n; j++)
      {
        if(i ==j)
        {
          I[i][j]=1;
        }
        else {I[i][j]=0;}
        
      }
    }

        cout<<" Matriz OG: "<<endl;
        cout<<"  "<<endl;
        cout<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<endl;
        cout<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<endl;
        cout<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<endl;
        cout<<"  "<<endl;
        
    cout<<"  INVERSA:  "<<endl;
    cout<<"  "<<endl;
    cout<<I[0][0]<<" "<<I[0][1]<<" "<<I[0][2]<<endl;
    cout<<I[1][0]<<" "<<I[1][1]<<" "<<I[1][2]<<endl;
    cout<<I[2][0]<<" "<<I[2][1]<<" "<<I[2][2]<<endl;
    cout<<"  "<<endl;
      
    
    cout<<" ANTES DEL METODO:  "<<endl;
    cout<<"  "<<endl;
    cout<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<endl;
    cout<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<endl;
    cout<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<endl;
    cout<<"  "<<endl;
    
cout<<"  INVERSA:  "<<endl;
cout<<"  "<<endl;
cout<<I[0][0]<<" "<<I[0][1]<<" "<<I[0][2]<<endl;
cout<<I[1][0]<<" "<<I[1][1]<<" "<<I[1][2]<<endl;
cout<<I[2][0]<<" "<<I[2][1]<<" "<<I[2][2]<<endl;
cout<<"  "<<endl;


        for (int i=0;i<n;i++){
                //Normaliza
                cout<<"Normaliza: "<<endl;
                    for (int i=0;i<n;i++){
                        diagonal = M[i][i];
                        
                        for(int j=0;j<n;j++){
                            if(j!=i){
                                NoDiagonal = M[i][j];
                                
                            }
                            if(diagonal!=0){
                                    NoDiagonal=NoDiagonal/diagonal;
                                    M[i][j]=NoDiagonal;
                                    
                            }
                                else if(diagonal==0){
                                    M[i][j]=M[i+1][j];
                                    
                                    if(i==n-1){
                                        M[i][j]=M[i-1][j];
                                        
                                    }
                                }
                                if(j==n-1){
                                    diagonal=diagonal/diagonal;
                                    M[i][i]=diagonal;
                                    
                                }
                        }
                    }
            
        cout<<"  INVERSA ANTES DE OPERAR:  "<<endl;
        cout<<"  "<<endl;
        cout<<I[0][0]<<" "<<I[0][1]<<" "<<I[0][2]<<endl;
        cout<<I[1][0]<<" "<<I[1][1]<<" "<<I[1][2]<<endl;
        cout<<I[2][0]<<" "<<I[2][1]<<" "<<I[2][2]<<endl;
        cout<<"  "<<endl;
                // Comienza a Operar
            cout<<" ANTES DEL if:  "<<endl;
            cout<<"  "<<endl;
            cout<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<endl;
            cout<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<endl;
            cout<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<endl;
            cout<<"  "<<endl;
         
            cout<<" ANTES DEL if INVERSA:  "<<endl;
            cout<<"  "<<endl;
            cout<<I[0][0]<<" "<<I[0][1]<<" "<<I[0][2]<<endl;
            cout<<I[1][0]<<" "<<I[1][1]<<" "<<I[1][2]<<endl;
            cout<<I[2][0]<<" "<<I[2][1]<<" "<<I[2][2]<<endl;
            cout<<"  "<<endl;
            float pivot=M[i][i];
                if( pivot==1)
                {
                    if( i==0){
                        //Se le resta Constante*f1 a todo F2
                        if( M[i+1][0] !=0
                           //|| M[i+1][2]!=0
                           ){
                            float restar1=M[i+1][0];
                            M[i+1][0]= M[i+1][0]-restar1*M[i][0];
                            M[i+1][1]= M[i+1][1]-restar1*M[i][1];
                            M[i+1][2]= M[i+1][2]-restar1*M[i][2];
                            
                            I[i+1][0]= I[i+1][0]-restar1*I[i][0];
                            I[i+1][1]= I[i+1][1]-restar1*I[i][1];
                            I[i+1][2]= I[i+1][2]-restar1*I[i][2];
                        }
                            
                        //Se le resta Constante*f1 a todo F3
                        if( M[i+2][0] !=0
                           //|| M[i+2][1]!=0
                           ){
                            
                            cout<<"entra a borrar f3"<<endl;
                            float restar2=M[i+2][0];
                            M[i+2][0]= M[i+2][0]-restar2*M[i][0];
                            M[i+2][1]= M[i+2][1]-restar2*M[i][1];
                            M[i+2][2]= M[i+2][2]-restar2*M[i][2];
                            
                            I[i+2][0]= I[i+2][0]-restar2*I[i][0];
                            I[i+2][1]= I[i+2][1]-restar2*I[i][1];
                            I[i+2][2]= I[i+2][2]-restar2*I[i][2];
                        }
                    }
                    
                    if( i==1){
                        
                        //Se le resta Constante*f2 a todo F1
                        if( M[i-1][1] !=0
                           //|| M[i-1][2]!=0
                           ){
                            
                            float restar1=M[i-1][1];
                            
                            M[i-1][0]= M[i-1][0]-restar1*M[i][0];
                            M[i-1][1]= M[i-1][1]-restar1*M[i][1];
                            M[i-1][2]= M[i-1][2]-restar1*M[i][2];
                            
                            I[i-1][0]= I[i-1][0]-restar1*I[i][0];
                            I[i-1][1]= I[i-1][1]-restar1*I[i][1];
                            I[i-1][2]= I[i-1][2]-restar1*I[i][2];
                        }

                        //Se le resta Constante*f2 a todo F3
                        if( M[i+1][1] !=0
                          // || M[i+1][1]!=0
                           ){
                            cout<<"entra a borrar f3"<<endl;

                            float restar2=M[i+1][1];
                            M[i+1][0]= M[i+1][0]-restar2*M[i][0];
                            M[i+1][1]= M[i+1][1]-restar2*M[i][1];
                            M[i+1][2]= M[i+1][2]-restar2*M[i][2];
                            
                            I[i+1][0]= I[i+1][0]-restar2*I[i][0];
                            I[i+1][1]= I[i+1][1]-restar2*I[i][1];
                            I[i+1][2]= I[i+1][2]-restar2*I[i][2];
                        }

                        
                    }
                    if( i==2){
                        
                        //Se le resta Constante*f2 a todo F1
                        if(
                           //M[i-1][0] !=0 ||
                           M[i-1][2]!=0){
                            float restar1=M[i-1][2];
                            M[i-1][0]= M[i-1][0]-restar1*M[i][0];
                            M[i-1][1]= M[i-1][1]-restar1*M[i][1];
                            M[i-1][2]= M[i-1][2]-restar1*M[i][2];
                               
                            I[i-1][0]= I[i-1][0]-restar1*I[i][0];
                            I[i-1][1]= I[i-1][1]-restar1*I[i][1];
                            I[i-1][2]= I[i-1][2]-restar1*I[i][2];
                        }

                        //Se le resta Constante*f1 a todo F3
                        if(
                           //M[i-2][1] !=0 ||
                           M[i-2][2]!=0){
                            float restar2=M[i-2][2];
                            M[i-2][0]= M[i-2][0]-restar2*M[i][0];
                            M[i-2][1]= M[i-2][1]-restar2*M[i][1];
                            M[i-2][2]= M[i-2][2]-restar2*M[i][2];
                               
                            I[i-2][0]= I[i-2][0]-restar2*I[i][0];
                            I[i-2][1]= I[i-2][1]-restar2*I[i][1];
                            I[i-2][2]= I[i-2][2]-restar2*I[i][2];
                        }
                    }
                }
            //Termina la operacion
            // Comienza la normalizacion final
           
            for (int i=0;i<n;i++){
                diagonal = M[i][i];
                
                for(int j=0;j<n;j++){
                    if(j!=i){
                        NoDiagonal = M[i][j];
                        
                    }
                    if(diagonal!=0){
                            NoDiagonal=NoDiagonal/diagonal;
                            M[i][j]=NoDiagonal;
                            
                    }
                        if(j==n-1){
                            diagonal=diagonal/diagonal;
                            M[i][i]=diagonal;
                            
                        }
                    }
                }
                //Termina la normalizacion final
                
        }
            cout<<" despues DEL if:  "<<endl;
            cout<<"  "<<endl;
            cout<<M[0][0]<<" "<<M[0][1]<<" "<<M[0][2]<<endl;
            cout<<M[1][0]<<" "<<M[1][1]<<" "<<M[1][2]<<endl;
            cout<<M[2][0]<<" "<<M[2][1]<<" "<<M[2][2]<<endl;
            cout<<"  "<<endl;
            cout<<" INVERSA: "<<endl;
            cout<<I[0][0]<<" "<<I[0][1]<<" "<<I[0][2]<<endl;
            cout<<I[1][0]<<" "<<I[1][1]<<" "<<I[1][2]<<endl;
            cout<<I[2][0]<<" "<<I[2][1]<<" "<<I[2][2]<<endl;
            cout<<"  "<<endl;
            

    
    
    //cofactores
    cout<<" "<<endl;
    cout<<"2.Cofactores:"<<endl;
    cout<<" "<<endl;
    
    ////////////////////////
    //Transpuesta
    ////////////////
    cout<<" N: "<<endl;
    cout<<" "<<endl;
    cout<<N[0][0]<<","<<N[0][1]<<","<< N[0][2] <<endl;
    cout<<N[1][0]<<","<<N[1][1]<<","<< N[1][2] <<endl;
    cout<<N[2][0]<<","<<N[2][1]<<","<< N[2][2] <<endl;
    cout<<" "<<endl;
    
   
    float Nt[n][n];
    
    ///se hace N
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if ( i != j && i>j)
            {
                float arriba=N[i][j];
                float abajo=N[j][i];
                
                N[i][j] =abajo;
                N[j][i] = arriba;
                
            }
        }
    }
    //marranada de transpuesta
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            Nt[i][j]=N[i][j];
        }
    }
    
    cout<<" N: "<<endl;
    cout<<" "<<endl;
    cout<<N[0][0]<<","<<N[0][1]<<","<< N[0][2] <<endl;
    cout<<N[1][0]<<","<<N[1][1]<<","<< N[1][2] <<endl;
    cout<<N[2][0]<<","<<N[2][1]<<","<< N[2][2] <<endl;
    cout<<" "<<endl;
    
    cout<<" Nt: "<<endl;
    cout<<" "<<endl;
    cout<<Nt[0][0]<<","<<Nt[0][1]<<","<< Nt[0][2] <<endl;
    cout<<Nt[1][0]<<","<<Nt[1][1]<<","<< Nt[1][2] <<endl;
    cout<<Nt[2][0]<<","<<Nt[2][1]<<","<< Nt[2][2] <<endl;
    cout<<" "<<endl;
    
    
    
    ////////////////////////
    //Determinante
    ////////////////
    
    int a;
    
   for (int i=0;i<n;i++){
        a=N[0][i];
        cout<<"a:"<<a<<endl;
            if(i==0){
                b=a*((N[1][1]*N[2][2])-(N[1][2]*N[2][1]));
                cout<<"b:"<<b<<endl;
            }
            if(i==1){
                c=a*((N[0][1]*N[2][2])-(N[2][1]*N[0][2]));
                cout<<"c:"<<c<<endl;
            }
            if(i==2){
                d=a*((N[1][0]*N[2][1])-(N[2][0]*N[1][1]));
                cout<<"d:"<<d<<endl;
            }
            
    }
    
    det=b-c+d;
    
    cout<<" "<<endl;
    cout<<"a:"<<a<<endl;
    cout<<" "<<endl;
    cout<<"b:"<<b<<endl;
    cout<<" "<<endl;
    cout<<"c:"<<c<<endl;
    cout<<" "<<endl;
    cout<<"d:"<<d<<endl;
    cout<<" "<<endl;
    cout<<"det:"<<det<<endl;
    cout<<" "<<endl;
    
    //Adjunta
    
    float f;
    float g;
    float h;
    float k;
    float l;
    float m;
    float o;
    float p;
    float q;
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++ ){
            if(i==0 && j==0){
                f=(N[1][1]*N[2][2])-(N[1][2]*N[2][1]);
            }
            if(i==0 && j==1){
                g=(N[1][0]*N[2][2])-(N[1][2]*N[2][0]);
                g=g*-1;
            }
            if(i==0 && j==2){
                h=(N[1][0]*N[2][1])-(N[1][1]*N[2][0]);
                
            }
            if(i==1 && j==0){
                k=(N[0][1]*N[2][2])-(N[0][2]*N[2][1]);
                k=k*-1;
            }
            if(i==1 && j==1){
                l=(N[0][0]*N[2][2])-(N[0][2]*N[2][0]);
            }
            if(i==1 && j==2){
                m=(N[0][0]*N[2][1])-(N[0][1]*N[2][0]);
                m=m*-1;
            }
            
            if(i==2 && j==0){
                //de ISA o=(N[0][1]*N[1][2])-(N[1][0]*N[0][2]);
                o=(N[0][1]*N[1][2])-(N[1][1]*N[0][2]);
            }
           
            if(i==2 && j==1){
                p=(N[0][0]*N[1][2])-(N[1][0]*N[0][2]);
                p=p*-1;

            }
            if(i==2 && j==2){
                q=(N[0][0]*N[1][1])-(N[1][0]*N[0][1]);
            }
        }
    }
    
    float Adj[3][3]={
        {f,g,h},
        {k,l,m},
        {o,p,q}
    };
    
    cout<<" "<<endl;
    cout<<"Adjunta:  "<<endl;
    cout<<Adj[0][0]<<","<<Adj[0][1]<<","<< Adj[0][2] <<endl;
    cout<<Adj[1][0]<<","<<Adj[1][1]<<","<< Adj[1][2] <<endl;
    cout<<Adj[2][0]<<","<<Adj[2][1]<<","<< Adj[2][2] <<endl;
    cout<<" "<<endl;
    
    //Matriz inversa
    
    float inv[3][3]={
        {f/det,g/det,h/det},
        {k/det,l/det,m/det},
        {o/det,p/det,q/det}
    };
    
    cout<<" "<<endl;
    cout<<"Inversa:  "<<endl;
    cout<<inv[0][0]<<","<<inv[0][1]<<","<< inv[0][2] <<endl;
    cout<<inv[1][0]<<","<<inv[1][1]<<","<< inv[1][2] <<endl;
    cout<<inv[2][0]<<","<<inv[2][1]<<","<< inv[2][2] <<endl;
    cout<<" "<<endl;
    

            ofstream myInv ("inversas.txt");
            if (myInv.is_open()){
                myInv<<"Inversa por gauss:"<<endl;
                myInv<<I[0][0]<<" "<<I[0][1]<<" "<<I[0][2]<<endl;
                myInv<<I[1][0]<<" "<<I[1][1]<<" "<<I[1][2]<<endl;
                myInv<<I[2][0]<<" "<<I[2][1]<<" "<<I[2][2]<<endl;
                
                myInv<<" "<<endl;
                myInv<<"Inversa por cofactores: "<<endl;
                myInv<<inv[0][0]<<","<<inv[0][1]<<","<< inv[0][2] <<endl;
                myInv<<inv[1][0]<<","<<inv[1][1]<<","<< inv[1][2] <<endl;
                myInv<<inv[2][0]<<","<<inv[2][1]<<","<< inv[2][2] <<endl;
                
            }
            
    
            
                    
                
                
            
        
                
            
            

    
    
      
        
       
        
    return 0;
        
}
    
  
 


