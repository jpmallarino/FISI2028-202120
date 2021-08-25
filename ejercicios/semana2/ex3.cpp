#include <iostream>
#include <fstream>

using namespace std;

#define is_this_a_variable 3.14159

float glb_x = 0;
int glb_i = 0;

int main(void){
    unsigned int j = -1;
    cout<<"Variables and inputs"<<endl;
    cout<<"Value of 'glb_x'? "<<glb_x<<endl;
    cout<<"Value of 'glb_i'? "<<glb_i<<endl;
    cout<<"Value of 'j'? "<<j<<endl;

    cout<<"\nValue for glb_x[float]? ";
    cin>>glb_x;
    cerr<<"New value of 'glb_x'? "<<glb_x<<endl;
    cout<<"Value for glb_i[int]? ";
    cin>>glb_i;
    cerr<<"New value of 'glb_i'? "<<glb_i<<endl;
    cout<<"Value for j[unsigned int]? ";
    cin>>j;
    cerr<<"New value of 'j'? "<<j<<endl;

    return 0;
}
