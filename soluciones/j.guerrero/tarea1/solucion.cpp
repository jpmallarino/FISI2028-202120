#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

vector<uint> vector_with_ones_every_n(uint size, uint n) {
vector<uint> r(size,0);
for(uint i=0; i<size; i++) {
r[i] = (i%n == 0);
}
return r;
}

vector<uint> multiply_polynomials(vector<uint> p1, vector<uint> p2){
uint N = 0;
if (p1.size() != p2.size()){
cerr << "Not implemented: attempting to multiply two coefficient vectors of ddiferent size" << endl;
exit(1);
} else {
N = p1.size();
}

vector<uint> r(N,0);
for(uint i=0; i<N; i++) {
for(uint j=0; j<N; j++) {
if (i+j < N){
r[i+j] += p1[i]*p2[j];
}
}
}
return r;
}

set<uint> check_vector(vector<uint> vec, string kind, uint max=UINT_MAX) {
set<uint> S(vec.begin(),vec.end());
if (S.empty()) {
cerr << "empty "+kind+" are not allowed for integer_partitions" << endl;
exit(1);
}

if (S.size() != vec.size()) {
cerr << "repeated "+kind+" are not allowed for integer_partitions" << endl;
exit(1);
}

uint s_max = *S.end(); 
if (s_max >= max) {
cerr << kind+" greater than n are not allowed for integer_partitions" << endl;
exit(1);
}

uint s_min = *S.begin();
if (s_min == 0) {
cerr << "zero "+kind+" are not allowed for integer_partitions" << endl;
exit(1);
}
return S;
}

uint integer_partitions(uint n, vector<uint> factors) {
if (n == 0){
return 1;
}
check_vector(factors,"factors");
vector<uint> prod,p_i;
prod = vector_with_ones_every_n(n+1,factors[0]);
for(int i=1; i<factors.size(); i++) {
p_i = vector_with_ones_every_n(n+1,factors[i]);
prod = multiply_polynomials(prod,p_i);
}
return prod[n];
}

uint integer_partitions_with_stops(uint n, vector<uint> factors, vector<uint> stops) {
set<uint> stops_set = check_vector(stops,"stops",n);
stops_set.insert(0);
stops_set.insert(n);
vector<uint> part_sizes(stops_set.size()-1,0);
transform(++stops_set.begin(),stops_set.end(),stops_set.begin(),part_sizes.begin(),[](uint a, uint b){return a-b;});

vector<uint> parts_ways(part_sizes.size(),0);
for(int i=0; i<part_sizes.size(); i++){
parts_ways[i] = integer_partitions(part_sizes[i],factors);
}
return accumulate(parts_ways.begin(),parts_ways.end(),1,[](uint a,uint b){return a*b;});
}

int main(){
bool tiene_paradas = false;
uint n,i,j,tmp;
vector<uint> p,m;
cout << "Inserte el número de escalones (n): "; cin >> n;
cout << "Inserte el número de pasos (i): "; cin >> i;
cout << "Inserte las " << i << " longitudes de cada paso p_i:\n";
for(int k=0;k<i;k++){
cin >> tmp;
p.push_back(tmp);
}
cout << "Inserte el número de paradas (j): "; cin >> j;
tiene_paradas = (j!=0);
if (tiene_paradas) {
cout << "Inserte las " << j << " longitudes de cada parada m_j:\n";
for(int k=0;k<j;k++){
cin >> tmp;
m.push_back(tmp);
}
}
if (tiene_paradas) {
cout << "Con " << n << " escalones, pasos de tamaños { ";
for(int k=0;k<i;k++){
cout << p[k] << " ";
}
cout << "}, y paradas obligadas en { ";
for(int k=0;k<j;k++){
cout << m[k] << " ";
}
cout << "}, el número de maneras es " << integer_partitions_with_stops(n,p,m) << endl;
} else {
cout << "Con " << n << " escalones y pasos de tamaños { ";
for(int k=0;k<i;k++){
cout << p[k] << " ";
}
cout << "}, el número de maneras es " << integer_partitions(n,p) << endl;
}
}