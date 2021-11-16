// TareaMetodos_NicolleBermudez
#include <iostream>
#include <string>
#include <vector>
#include<algorithm>

using namespace std;

int punto_a(int escalones){
    if (escalones == 1) 
    {
        return 1;
    }
    else if (escalones == 2){
        return 2;
    }
    vector<int> pasos;
    pasos.push_back(1);
    pasos.push_back(2);
    for (int i = 2; i < escalones; i++)
    {
        pasos.push_back(pasos[i-1]+pasos[i-2]);
    }
    cout << pasos[escalones-1];
    return pasos[escalones-1];
    

}

vector<string> split(string str, char pattern) {
    
    int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> results;
    
    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }
    
    return results;
}

bool existeEnVector(vector<string> v, string busqueda) {
    return find(v.begin(), v.end(), busqueda) != v.end();
}
bool existeEnVectori(vector<int> v, int busqueda) {
    return find(v.begin(), v.end(), busqueda) != v.end();
}

bool sumar(string a,int b, int c)
{
    int suma = 0;
    for(char i : a){
        int digito = i - '0';
        suma += digito;
    }
    if (suma + b > c) return false;
    return true;
    
    
}
    

int punto_b(int num_escalones, int num_pasos, vector<int> pasos){
    
    int respuesta = 0;
    std:: vector<string> vec;
    for (int i = 0; i < num_escalones; i++)
    {
        for (int j : pasos)
        {
            string caracter = to_string(j);
            if (!existeEnVector(vec, caracter))
            {
                vec.push_back(caracter);
            }
            int tam_vec = vec.size();
            for (int k = 0; k < tam_vec; k++)
            {
                string uni = vec[k] + caracter;
                if (!existeEnVector(vec, uni) && uni.length() <= num_escalones && sumar(vec[k], j, num_escalones))
                {
                    vec.push_back(uni);
                }
            }
        }
    }


    for(string i : vec){
        int sumaC = 0;
        
        for(char j : i){
            int digito = j - '0';
            sumaC += digito;
        }
        if (sumaC == num_escalones)
        {
            respuesta += 1;
        }
        sumaC = 0;
        
    }
    return respuesta;
    
}

int punto_c(int num_pasos, vector<int> pasos, int escalones, int parada){
    int respuesta = punto_b(parada, num_pasos, pasos);
    respuesta  += punto_b(escalones-parada, num_pasos, pasos);
    return respuesta;
}

int punto_d(vector<int> paradas, int num_pasos, vector<int> pasos, int escalones){
    int suma = 0;
    int piso = 0;
    sort(paradas.begin(), paradas.end());
    for(int i : paradas){
        suma += punto_b(i-piso, num_pasos, pasos);
        piso = i;
    }
    suma += punto_b(escalones-piso, num_pasos, pasos);

    return suma;
}

int main(){
    
    char opcion = 'o';
    cout << "Hola! que punto quieres hacer? " << endl;
    cout << "a/b?" << endl;
    cin >> opcion;
    if (opcion == 'a')
    {
        int escalones = 0;
        cout << "Cuantos escalones va subir?";
        cin >> escalones;
        punto_a(escalones);
    }
    else if (opcion == 'b')
    {
        int num_escalones = 0;
        int num_pasos = 0;
        int num_paradas = 0;
        std:: vector<int> pasos;
        std:: vector<int> paradas;
        cout << "Cuantos escalones va subir?";
        cin >> num_escalones;
        cout << "Cuantos pasos puede dar?" << endl;
        cin >> num_pasos;
        cout << "Por favor, ingrese los pasos uno a uno";
        for (int i = 0; i < num_pasos; i++)
        {
            int paso = 0;
            cin >> paso;
            if (existeEnVectori(pasos, paso))
            {
                cout << "Ese paso ya estaba";
                return 0;
            }
            pasos.push_back(paso);
        }

        cout << "Cuantos paradas tendrá?" << endl;
        cin >> num_paradas;
        cout << "Por favor, ingrese los escalones de la(s) parada(s)";
        for (int i = 0; i < num_paradas; i++)
        {
            int paradita = 0;
            cin >> paradita;
            if (existeEnVectori(paradas, paradita) || paradita < 1 || paradita >= num_escalones)
            {
                cout << "no cumples con las reglas";
                return 0;
            }
            paradas.push_back(paradita);
            
        }
        
        cout << punto_b(num_escalones, num_pasos, pasos);
    }
    else{
        cout << "No ingresaste una opcion valida";
    }
    

}

