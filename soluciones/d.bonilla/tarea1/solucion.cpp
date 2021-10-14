#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


using namespace std;

/* --- Prototipos de funciones para leer y escribir archivos --- */

/**
 * @brief Retorna el número de filas y columnas de la matriz cuadrada guardada en el archivo.
 * 
 * @param file_name Nombre del archivo donde está guardada la matriz. 
 * @return int Número de filas y columnas de la matriz cuadrada.
 */
int matrix_size(const char* file_name);

/**
 * @brief Carga la matriz de un archivo a un arreglo. Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar. 
 * 
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @param file_name Nombre del archivo donde está guardada la matriz.
 * @return Puntero hacia el primer elemento de la matriz.
 */
double* load_matrix( const char* file_name, const int n );

/**
 * @brief Imprime una matriz en un archivo.
 * 
 * @param file_name Nombre del archivo donde se va a guardar la matriz.
 * @param p_matrix Puntero al primer elemento de la matriz que se quiere imprimir.
 * @param n Número de filas y columnas de la matriz cuadrada..
 * @return 1 si el archivo pudo abrirse, 0 de lo contrario.
 */
int print_matrix( const char* file_name, double* p_matrix, const int n );

/* --- Prototipos de funciones usadas para gauss-jordan --- */

/**
 * @brief Crea una matriz identidad de nxn. Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar.
 * 
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return double* Puntero hacia el primer elemento de la matriz.
 */
double* identity(int n);

/**
 * @brief Intercambia de posición dos filas de la matriz.
 * 
 * @param i Fila a intercambiar de la matriz, i >= 0 && i<n.
 * @param j Fila a intercambiar de la matriz, j >= 0 && j<n.
 * @param p_matrix Puntero hacia el primer elemento de la matriz.
 * @param n Número de filas y columnas de la matriz cuadrada.
 */
void interchange(int i, int j, double* p_matrix, const int n);

/**
 * @brief Multiplica la fila de la matriz por una constante.
 * 
 * @param i Fila de la matriz, i >= 0 && i<n.
 * @param s Constante que multiplica a toda la fila
 * @param p_matrix Puntero hacia el primer elemento de la matriz.
 * @param n Número de filas y columnas de la matriz cuadrada.
 */
void multiply_by(int i, double s, double* p_matrix, const int n);

/**
 * @brief En la misma matriz resta un multiplo de la fila j a la fila i.
 * 
 * @param i Fila a intercambiar de la matriz, i >= 0 && i<n.
 * @param j Fila a intercambiar de la matriz, j >= 0 && j<n.
 * @param s Constante que multiplica a toda la fila j.
 * @param p_matrix Puntero hacia el primer elemento de la matriz.
 * @param n Número de filas y columnas de la matriz cuadrada.
 */
void substract_multiple(int i, int j, double s, double* p_matrix,const int n);

/**
 * @brief Busca la primera fila con pivote en la columna i-esima
 * 
 * @param i Fila sin pivote.
 * @param p_matrix Puntero hacia el primer elemento de la matriz.
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return Posición de la fila con pivote en la columna i
 */
int buscar_pivote(int i, double* p_matrix, const int n);

/**
 * @brief Aplica el método de eliminación Gauss-Jordan a la matriz dada por parámetro. Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar.
 * 
 * @param p_matriz Puntero hacia el primer elemento de la matriz.
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return double* Puntero hacia el primer elemento de la matriz inversa.
 */
double* gauss_jordan( double *p_matriz, const int n );

/* --- Prototipos de funciones usadas para cofactores --- */

/**
 * @brief Calcula el determinante de la matriz usando una matriz triangular.
 * 
 * @param p_matrix Puntero hacia el primer elemento de la matriz.
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return double Determinante de la matriz.
 */
double det( double* p_matrix, const int n);

/**
 * @brief Crea la minor matrix de la entrada ij de la matriz, Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar.
 * 
 * @param i coordenada i de la entrada i-esima de la matriz.
 * @param j coordenada j de la entrada j-esima de la matriz.
 * @param p_matrix Puntero hacia el primer elemento de la matriz original.
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return double* Puntero hacia el primer elemento de la minor matrix.
 */
double* minor_matrix(int i_p, int j_p, double* p_matrix, const int n);

/**
 * @brief Crea la matriz de cofactores de la matriz dada por parametro, Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar.
 * 
 * @param matrix_pointer Puntero hacia el primer elemento de la matriz original.
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return double* Puntero hacia el primer elemento de la matriz de cofactores.
 */
double* cofactor_matrix( double* p_matrix, const int n );

/**
 * @brief Multiplica una matriz por una constante
 * 
 * @param p_matrix  Puntero hacia el primer elemento de la matriz original.
 * @param s Constante que multiplica a toda la fila j.
 * @param n Número de filas y columnas de la matriz cuadrada.
 */
void multiply_matrix( double* p_matrix, double s,const int n );

/**
 * @brief Retorna la transpuesta de la matriz
 * 
 * @param matrix_pointer Puntero hacia el primer elemento de la matriz original.
 * @param n Número de filas y columnas de la matriz cuadrada.
 * @return double* Puntero hacia el primer elemento de la matriz transpuesta. */
double* transpose( double* p_matrix, const int n );

int main( )
{

    int m_size = matrix_size("matriz");

    cout << "Filas y columnas: " << m_size << endl;

    double *m_p = load_matrix("matriz",m_size);

    double m_det = det(m_p,m_size);

    cout << "Determinante: " << m_det << endl;

    delete[] m_p;
    m_p = NULL;

    if( m_det != 0 )
    {
        double *m_in = load_matrix("matriz",m_size);

        double *m_inv = cofactor_matrix(m_in,m_size);

        multiply_matrix(m_inv,1/m_det,m_size);

        double* sol2 = transpose(m_inv,m_size);

        cout << "La inversa de la matriz se guarda correctamente: "<< print_matrix("cf_inv_mat",sol2,m_size) << endl;

        delete[] sol2;
        sol2 = NULL;

        delete[] m_in;
        m_in = NULL;

        delete[] m_inv;
        m_inv = NULL;

        double *m_in_gj = load_matrix("matriz",m_size);

        double *m_inv_gj = gauss_jordan(m_in_gj,m_size);

        cout << "La inversa de la matriz se guarda correctamente: "<< print_matrix("gj_inv_mat",m_inv_gj,m_size) << endl;

        delete[] m_in_gj;
        m_in = NULL;

        delete[] m_inv_gj;
        m_inv = NULL;

    }

    return 0;

}

//Retorna el número de filas y columnas de la matriz cuadrada guardada en el archivo.
int matrix_size(const char* file_name)
{

    FILE *fp = fopen(file_name,"r");

    if( fp != NULL)
    {

        char c,a = 0;
        int n = 0;

        while( (c = fgetc(fp)) != EOF)
        {   

            if( c == '\n')
            {
                ++n;
            }
            a = c;
        }
        
        if( a != '\n' && c == EOF )
        {
            ++n;
        }
        
        fclose(fp);

        return n;

    }

    return 0;

}

//Carga la matriz de un archivo a un arreglo. Hay que borrar de manera adecuada el arreglo una vez se termine de usar.
double* load_matrix( const char* file_name, const int n )
{

    double* matrix = identity(n);

    fstream myfile(file_name,ios_base::in);

    if(myfile.is_open())
    {
        
        double a = 0;
        int i = 0;

        while( myfile >> a )
        {

            if(i < n*n)
            {
                *(matrix + i) = a;
                ++i;
            }
        
        }

        myfile.close();

    }
    
    return matrix;

}

//Imprime una matriz en un archivo.
int print_matrix( const char* file_name, double* p_matrix, const int n )
{

    if( p_matrix != NULL )
    {

        ofstream ofs;
        ofs.open(file_name,ofstream::trunc);

        if(ofs.is_open())
        {
            int i = 0;

            while( i < n*n )
            {
                
                if(*(p_matrix+i)>=0 )
                {
                    ofs << " ";
                }

                ofs << to_string(*(p_matrix + i)) << "\t";

                if((i+1)%n == 0 && (i+1) != n*n)
                {

                    ofs << endl;

                }

                ++i;

            }

            ofs.close();

            return 1;

        }

    }

    return 0;

}

//Crea una matriz identidad de nxn. Hay que borrar de manera adecuada el arreglo una vez se termine de usar.
double* identity( const int n )
{

    double *ident = new double [n*n];

    if( ident != NULL )
    {

        int i = 0;

        while( i<n*n )
        {

            *(ident + i) = (i%(n+1))?0.0:1.0;
            ++i;
        }

    }

    return ident;

}

//Intercambia de posición dos filas de la matriz.
void interchange(int i, int j, double* p_matrix, const int n)
{

    if( i<n && j<n)
    {

        double temp = 0;
        int f = 0;

        while( f < n )
        {

            temp = *(p_matrix + i*n + f);
            *(p_matrix + i*n + f) = *(p_matrix + j*n + f);
            *(p_matrix + j*n + f) = temp;
            ++f;

        }

    }

}

//Multiplica la fila de la matriz por una constante.
void multiply_by(int i, double s, double* p_matrix, const int n)
{

    if( i>=0 && i<n )
    {

        int j = i*n;

        while(j < (i+1)*n)
        {
                
            *(p_matrix+j) *= s;
            ++j;

        }

    }

}

//En la misma matriz resta un multiplo de la fila j a la fila i.
void substract_multiple(int i, int j, double s, double* p_matrix, const int n)
{

    if( (i<n) && (j<n))
    {

        int f = 0;

        while( f < n )
        {

            *(p_matrix + i*n + f) -= s*(*(p_matrix + j*n + f));
            ++f;

        }

    }

}

// Busca la primera fila con pivote en la columna i-esima
int buscar_pivote(int i, double* p_matrix, const int n)
{

    int j = i+1;

    while( *(p_matrix+j*n+i) == 0 && j < n)
    {
        ++j;
    }

    return j;

}

//Aplica el método de eliminación Gauss-Jordan a la matriz dada por parámetro. Hay que borrar de manera adecuada el arreglo una vez se termine de usar.
double* gauss_jordan( double* p_matrix, const int n )
{
    
    double *i_matrix = identity(n);
    
    if( p_matrix != NULL && i_matrix != NULL)
    {

        int i = 0;

        while( i < n )
        {
            
            if((*(p_matrix+i*n+i)) == 0)
            {
                
                int p = buscar_pivote(i,p_matrix,n);

                interchange(i,p,p_matrix,n);
                interchange(i,p,i_matrix,n);

            }

            multiply_by(i,(1/(*(p_matrix+i*n+i))),i_matrix,n);
            multiply_by(i,(1/(*(p_matrix+i*n+i))),p_matrix,n);

            int j = i+1;

            while( j < n )
            {

                substract_multiple(j,i,*(p_matrix+j*n+i),i_matrix,n);
                substract_multiple(j,i,*(p_matrix+j*n+i),p_matrix,n);

                ++j;

            }

            ++i;

        }

        while( i > -1 )
        {

            multiply_by(i,(1/(*(p_matrix+i*n+i))),i_matrix,n);
            multiply_by(i,(1/(*(p_matrix+i*n+i))),p_matrix,n);

            int j = i-1;

            while( j > -1 )
            {
                
                substract_multiple(j,i,*(p_matrix+j*n+i),i_matrix,n);
                substract_multiple(j,i,*(p_matrix+j*n+i),p_matrix,n);
                --j;

            }

            --i;
            
        }

    }

    return i_matrix;

}

// Calcula el determinante de la matriz usando una matriz triangular.
double det( double* p_matrix, const int n)
{

    if( p_matrix != NULL )
    {

        int i = 0;
        double det = 1;

        while( i < n  && det != 0 )
        {
            
            if((*(p_matrix+i*n+i)) == 0)
            {
                
                int p = buscar_pivote(i,p_matrix,n);

                interchange(i,p,p_matrix,n);
                det *= -1;

                if( p == n )
                {

                    det *= 0;

                }

            }

            int j = i+1;

            while( j < n && det != 0 )
            {

                substract_multiple(j,i,*(p_matrix+j*n+i)/(*(p_matrix+i*n+i)),p_matrix,n);

                ++j;

            }

            ++i;

        }

        i = 0;

        while(i < n && det != 0)
        {
            det *= *(p_matrix+i*n+i);
            ++i;
        }

        return det;

    }

    return 0;
}

// Crea la minor matrix de la entrada ij de la matriz, Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar.
double* minor_matrix( int i_p, int j_p, double* p_matrix, const int n )
{

    double* i_matrix = identity(n-1);

    if( p_matrix != NULL  && (i_p < n && j_p < n) )
    {

        int f = 0;
        int c = 0;
        int p = 0;

        while( f < n*n )
        {
            
            if( !((i_p*n <= f && f < (i_p + 1)*n) || f == j_p + c*n ))
            {
                
                *(i_matrix + p) = *(p_matrix + f);

                ++p;

            }

            c += ((f+1)%n == 0)?1:0;
            ++f;

        }

    }

    return i_matrix;

}

// Crea la matriz de cofactores de la matriz dada por parametro, Hay que borrar de manera adecuada el arreglo retornado una vez se termine de usar.
double* cofactor_matrix( double* p_matrix, const int n )
{
    
    double* i_matrix = identity(n);

    if( p_matrix != NULL )
    {

        int f = 0;
        int c = 0;
        int p = 0;

        while( f < n*n )
        {

            double *actual = minor_matrix(c,p,p_matrix,n);

            *(i_matrix + f) = (pow(-1,p+c))*det(actual,n-1);

            delete[] actual;
            actual = NULL;

            ++p;
            if( p == 3 )
            {
                p = 0;
            }

            c += ((f+1)%n == 0)?1:0;
            ++f;

        }

    }

    return i_matrix;

}

// Multiplica una matriz por una constante
void multiply_matrix( double* p_matrix, double s,const int n )
{

    int i = 0;

    while( i < n*n )
    {

        *(p_matrix + i) *= s;

        ++i;

    }

}

double* transpose( double* p_matrix, const int n )
{

    int a = 0;
    int b = 0;
    int m = 0;
    
    double* i_matrix = identity(n);

    for( int j = 0; j < n; ++j )
    {

        for( int i = 0; i < n; ++i )
        {

            m = i*n + a;
            *(i_matrix + b) = *(p_matrix + m);
            b++;

        }

        ++a;

    }   

    return i_matrix;

}

