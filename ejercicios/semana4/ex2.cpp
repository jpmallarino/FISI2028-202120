#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(void){
    string s1,s2;
    cout<<"LCS"<<endl;
    cout<<"Primera cadena de caracteres: ";
    getline(cin,s1);
    cout<<"Segunda cadena de caracteres: ";
    getline(cin,s2);

    int l1 = s1.length();
    int l2 = s2.length();
    vector<int> redux_matrix( (l1 + 1) * (l2 + 1) );
    int v1,v2; // Temporary integer types
    for (int it = 0; it <= l1; it++)
        for (int jt = 0; jt <= l2; jt++) {
            redux_matrix[ it * (l2 + 1) + jt ] = 0;
            if (it > 0 && jt > 0) {
                if (s1.at(it-1) == s2.at(jt-1)) {
                    v1 = redux_matrix[ (it-1) * (l2 + 1) + (jt-1) ];
                    redux_matrix[it * (l2 + 1) + jt] = v1 + 1;
                    redux_matrix[it * (l2 + 1) + jt] = v1 + 1;
                } else {
                    v1 = redux_matrix[ (it) * (l2 + 1) + (jt-1) ];
                    v2 = redux_matrix[ (it-1) * (l2 + 1) + (jt) ];
                    redux_matrix[it * (l2 + 1) + jt] = v1 > v2 ? v1:v2;
                }
            }
        }
    cout<<"\nLCS:: "<<redux_matrix[(l1 + 1) * (l2 + 1) - 1]<<endl;

    return 0;
}
