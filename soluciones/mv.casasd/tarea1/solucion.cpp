/* 
 * Asignatura: Métodos Computacionales en Ciencias
 * Nombre: María Camila Casas Díaz
 * Código: 201813057
 */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>
#include <climits>
#include <vector>
#include <set>

using namespace std;

vector<uint> vector_n(uint size, uint n) {
	vector<uint> vec(size,0);
	for(uint i=0; i<size; i++) {
		vec[i] = (i%n == 0);
	}
	return vec;
}

set<uint> restricciones(vector<uint> vector, uint maximo=UINT_MAX) {
	set<uint> vector_en_revision(vector.begin(),vector.end());
	uint min = *vector_en_revision.begin();
	uint max = *vector_en_revision.end(); 

	if (vector_en_revision.empty()) {
		printf ("incalculable. i & j deben cumplir las condiciones; i>0 & j>0\n");
		exit(EXIT_FAILURE);}
	
	if (min == 0) {
		printf ("incalculable. pi & mj deben cumplir las condiciones; pi>0 & mj>0\n");
		exit(EXIT_FAILURE);}

	if (vector_en_revision.size() != vector.size()) {
		printf ("incalculable. pi & mj no pueden estar repetidos\n");
		exit(EXIT_FAILURE);}
	
	if (max >= maximo) {
		printf("incalculable. pi>n  \n");
		exit(EXIT_FAILURE);}

	return vector_en_revision;
}

vector<uint> multiplicacion(vector<uint> vec1, vector<uint> vec2){
	uint a = 0;
	if (vec1.size() != vec2.size()){
		printf("vectores de diferente tamaño \n");
		exit(EXIT_FAILURE);} 
	
	else{
		a = vec1.size();}
	
	vector<uint> vec(a,0);

	for (uint i=0; i<a; i++) {
		for (uint j=0; j<a; j++) {
			if (i+j < a){
				vec[i+j] += vec1[i]*vec2[j];
			}
		}
	}
	return vec;
}

uint subir_escalera(uint n, vector<uint> i) {
    if (n == 0 || n == 1) {
		return 1;
	}
	restricciones(i);
	vector<uint> p,pi;
	p = vector_n(n+1,i[0]);
	
	for(int j=1; j<i.size(); j++){
		pi = vector_n(n+1,i[j]);
		p = multiplicacion(p,pi);
	}
	return p[n];
}

uint subir_escalera_paradas(uint n, vector<uint> i, vector<uint> m) {
	set<uint> conjunto_paradas = restricciones(m, n);
	conjunto_paradas.insert(0);
	conjunto_paradas.insert(n);
	
	vector<uint> partes_div(conjunto_paradas.size()-1,0);
	transform(++conjunto_paradas.begin(),conjunto_paradas.end(),conjunto_paradas.begin(),partes_div.begin(),[](uint p1, uint p2){return p1-p2;});
	
	vector<uint> formas_por_partes(partes_div.size(),0);
	for(int j=0; j<partes_div.size(); j++){
		formas_por_partes[j] = subir_escalera(partes_div[j],i);
	}
	
	return accumulate(formas_por_partes.begin(),formas_por_partes.end(),1,[](uint f1,uint f2){return f1*f2;});
}

int main(){

	uint n,i,j,tmp;
	vector<uint> pi,mj;

	cout << " [n - Escalones totales] : "; cin >> n;
	cout << " [i - Pasos totales] : "; cin >> i;
	cout << " [pi - Conjunto finito de pasos] : \n";
	for (int k=0; k<i; k++){
		cin >> tmp;
		pi.push_back(tmp);
	}

	bool paradas = false;

	cout << " [j - Paradas totales] : "; cin >> j;
	if (paradas= (j!=0)) {
		cout << " [mj - Conjunto finito de paradas] : \n";
		for(int k=0;k<j;k++){
			cin >> tmp;
			mj.push_back(tmp);
		}
		cout << " El número de formas para subir la escalera de " << n << " pasos es: " << subir_escalera_paradas(n,pi,mj) << endl;
	}
	else {
		cout << " El número de formas para subir la escalera de " << n << " pasos es: " << subir_escalera(n,pi) << endl;}
	
return 1;

}