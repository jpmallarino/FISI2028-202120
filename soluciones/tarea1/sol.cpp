#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;


/*
	Cinco funciones auxiliares:
	- ver_vec que imprime el vector a un string
	- mult_vec que multiplica los elementos de un vector
	- max_vec que calcula el máximo de un vector
	- ordenar_dupla que ya la hicimos...
	- ordenar_vec que ordena el vector
*/
string ver_vec(int * const vec, int const n){
	ostringstream ss; // output string stream
    ss << "[ ";
    for (int k = 0; k < n; k++) {
        ss << vec[k] << ' ';
    }
    ss << "]";
    return ss.str();
}
int mult_vec(int *vec, int n){
	if (n <= 0)
		return 0;
	int mult = 1;
	for (int i = 0; i < n; i++)
		mult *= vec[i];
	return mult;
    // Por favor vean la librería <algorithm>, ¡tiene una función prod
    // que es la maravilla! No reinventar la rueda
}
int max_vec(int *vec, int n){
	if (n <= 0)
		return 0;
	int max = vec[0];
	for (int i = 0; i < n; i++)
		max = vec[i] > max ? vec[i]:max;
	return max;
    // Por favor vean la librería <algorithm>, ¡tiene una función max_element
    // que es la maravilla! No reinventar la rueda
}
bool ordenar_dupla(int &a, int &b){
	// asigna a y b tal que a <= b
	if (a > b){
	    int a_temp = a;
	    a = b;
	    b = a_temp;
	    return true;
	} else
		return false;
}
bool ordenar_vec(int *vec, int n){
	// No vamos a hacer un merge sort... sólo un simple sort
	// retorna verdadero o falso si tiene que ordenar o no respectivamente
	if (n>=2){
		// ¿tuvo que ordenar?
		bool ordeno = false;
		// supongo que el vector es ordenado
		bool es_ordenado;
		while (true) {
			// supongo que el vector es ordenado
			es_ordenado = true;
			// busco si hay algún cambio de orden -> no esta ordenado
			// la funcion ordenar_dupla ordena una pareja y simultáneamente
			// me dice si hubo algún reordenamiento.
			for (int i = 0; i < n-1; i++) {
				if ( ordenar_dupla(vec[i], vec[i+1]) ) {
					es_ordenado = false;
					ordeno = true;
				}
			}
			if (es_ordenado) {
				// si el vector esta ordenado, se sale del loop
				break;
			}
		}
		return ordeno;
	} else {
		return false;
	}
    // Por favor vean la librería <algorithm>, ¡tiene una función sort
    // que es la maravilla! No reinventar la rueda
}

/*
	Esta función es quien calculará los caminos de manera
	recursiva. Tenga presente que no estará optimizada de
	ninguna manera.
	- e es el escalón en el que estoy parado
	- n el número total de escalones para la meta
	- j el número de posibles saltos en cada paso
	- vec_j el vector de esos posibles saltos
	* Condición de terminación de recursión:
		caminos_rec(n,n,...) = 1
*/
int caminos_rec(int e,int n, int j, int *vec_j){
	if (e >= n)
		return e == n ? 1:0; // no me puedo pasar!
	int acumulador = 0;
	for (int i = 0; i < j; i++){
		int e_nuevo = e+vec_j[i];
		if (e_nuevo <= n)
			acumulador += caminos_rec(e_nuevo,n,j,vec_j);
	}
	return acumulador;
}

/*
	La función ´main´ recopilará todos los datos que necesitamos:
	n     - número de escaleras (Error 1)
	j     - número de saltos diferentes (Error 2)
	vec_j - vector con el número de escaleras para cada salto.
	        Error 3 y 4 son respectivamente valores negativos y repetidos
	k     - número de paradas obligadas (Error 5)
	vec_k - vector con la posición de los escalones correspondientes
	         a las paradas obligadas. Error 6 y 7 son respectivamente
	         valores fuera del rango y repetidos
*/
int main(void){
	int n = -1;
	int j = -1,k = -1;
	int *vec_j, *vec_k;

	cout << "Ingrese el numero de escaleras: ";
	cin >> n;
	// verifica j
	// NOTA: n = 0 es un caso especial, ¡0 caminos!
	if(n < 0){
		cerr << "[error] esperado: 'n'>=0 . El valor obtenido fue: " << n << endl; 
		return 1;
	}

	cout << "Cuantas pasos diferentes admite: ";
	cin >> j;
	// verifica j
	// NOTA: j = 0 es un caso especial, ¡no se puede subir!
	if(j <= 0){
		cerr << "[error+pasos] 'j>0' un entero. Valor obtenido: " << j << endl; 
		return 2;
	}
	vec_j = new int[j];

	cout << "Ingrese los escalones que sube en cada paso:" << endl;
	for( int a = 0; a < j; a++ ){
		cout << "  " ; cin >> vec_j[a];
		// verifica que estén en el rango
		// NOTA: si es cero, ¡habrian infinitos caminos!
		if (vec_j[a] <= 0){
			cerr << "[error+paso] 'escalones>0'. Valor obtenido: " << vec_j[a] << endl; 
			return 3;
		}
		// verifica que todos sean diferentes
		if( a > 0 ){
			for( int b = 0; b < a; b++ ){
				if (vec_j[b] == vec_j[a]){
					cerr << "[error+pass] sin repeticiones. Valor repetido: " << vec_j[a] << endl; 
					return 4;
				}
			}
		}
	}

	cout << "Cuantas paradas obligadas realizara: ";
	cin >> k;
	// verifica k
	// NOTA: k puede ser cero, o no hay paradas obligadas
	if(k < 0){
		cerr << "[error+paradas] 'k>=0' un entero. Valor obtenido: " << k << endl; 
		return 5;
	}
	vec_k = new int[k+1]; // Generalizo para cualquier # de paradas obligadas

	cout << "Ingrese los escalones en los que hay paradas oblitadas:" << endl;
	for( int a = 0; a < k; a++ ){
		cout << "  " ; cin >> vec_k[a];
		// verifica que estén en el rango
		if (vec_k[a] <= 0 || vec_k[a] >= n){
			cerr << "[error+paradas] '0<escalones<n' un entero. Valor obtenido: " << vec_k[a] << endl; 
			return 6;
		}
		// verifica que todos sean diferentes
		if( a > 0 ){
			int temp = vec_k[a];
			for( int b = 0; b < a; b++ ){
				if (vec_k[b] == temp){
					cerr << "[error+paradas] sin repeticiones. Valor repetido: " << temp << endl; 
					return 7;
				}
			}
		}
	}
	vec_k[k] = n;
	k = k + 1;
	// ordenar_vec(vec_k, k);

	cout << "\n\n\nResumen:\n";
	cout << "  n=" << n << endl;
	cout << "  j=" << j << " -> " << ver_vec(vec_j,j) << endl;
	cout << "    ATENCIÓN: hay al menos una parada obligatoria: ¡en la cima!" << endl;
	cout << "  k=" << k << " -> " << ver_vec(vec_k,k) << endl;

	int *caminos_entre_paradas;
	caminos_entre_paradas = new int[k];
	for (int i=0; i < k; i++){
		int escalones = vec_k[i] - ( i > 0 ? vec_k[i-1] : 0 ); // a = vec_k[i-1] if i > 0 else 0
		caminos_entre_paradas[i] = caminos_rec(0,escalones,j,vec_j);
		cout << "Parada "<< i+1 << " /" << k << endl;
		cout << "  trayecto: " << ( i > 0 ? vec_k[i-1] : 0 ) <<\
			" >>> " << vec_k[i] << endl;
		cout << "  escalones: "<< escalones << " -> caminos=" <<\
			caminos_entre_paradas[i] << endl;
	}
	cout << "Caminos totales para "<< n << " escalones: " <<\
		mult_vec(caminos_entre_paradas,k) << endl;

	delete [] vec_j, vec_j = nullptr;
	delete [] vec_k, vec_k = nullptr;
	return 0;
}
