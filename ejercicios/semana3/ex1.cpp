#include <iostream>
#include <string>

using namespace std;

int main(void){
    // What about text?
    char BUFFER1[16];
    string BUFFER2;
    cout<<"Capture line (1) -> "; cin.getline(BUFFER1,16);
    cout<<"Capture line (2) -> "; getline(cin,BUFFER2);
    cout<<"Captured lines:\n\t"<<BUFFER1<<"\n\t"<<BUFFER2<<endl;

    cout<<"Is there another way for BUFFER1? ";cin>>BUFFER1;
    cout<<"Is there another way for BUFFER2? ";cin>>BUFFER2;
    cout<<"Newly captured lines:\n\t"<<BUFFER1<<"\n\t"<<BUFFER2<<endl;

    return 0;
}
