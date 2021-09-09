#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct LCS {
    vector<string> v;
    int n;
};



int longest_common_subsequence_rec(string s1, string s2){
    if ( s1.length() == 0 || s2.length() == 0 )
        return 0;
    if(s1[0] == s2[0]){
        if ( s1.length() == 1 || s2.length() == 1 )
            return 1;
        string new_s1 = s1.substr(1);
        string new_s2 = s2.substr(1);
        return 1+longest_common_subsequence_rec(new_s1,new_s2);
    } else {
        int case1=0;
        int case2=0;
        if ( s1.length() > 1 ){
            string new_s1 = s1.substr(1);
            case1 = longest_common_subsequence_rec(new_s1,s2);
        }
        if ( s2.length() > 1 ){
            string new_s2 = s2.substr(1);
            case2 = longest_common_subsequence_rec(s1,new_s2);
        }
        return max(case1,case2);
    }
}


int longest_common_subsequence(string s1, string s2){
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
    return redux_matrix[(l1 + 1) * (l2 + 1) - 1];
}

int main(void){
    string s1,s2;
    cout<<"LCS"<<endl; // Largest Common Subsequence
    cout<<"Primera cadena de caracteres: ";
    getline(cin,s1);
    cout<<"Segunda cadena de caracteres: ";
    getline(cin,s2);

    cout<<"\nLCS:: "<<longest_common_subsequence(s1,s2)<<endl;

    cout<<"LCS_rec:: "<<longest_common_subsequence_rec(s1,s2)<<endl;

    return 0;
}
