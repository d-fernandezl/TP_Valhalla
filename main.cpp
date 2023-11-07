#include <iostream>
#include "ABBv2.hpp"
#include "Placa.hpp"

using namespace std;

bool menor(int dato_1, int dato_2);
bool igual(int dato_1, int dato_2);

int main()
{
    ABB<int, menor, igual> arbolito;
    arbolito.alta(12);
    arbolito.alta(8);
    arbolito.alta(11);
    arbolito.alta(9);
    arbolito.alta(20);
    arbolito.alta(15);
    arbolito.alta(18);

    /*12 8 11 9 20 15 18*/
    /* 12 8 20 11 9*/
    /*
    vector<int> numeros = arbolito.postorder();
    for (size_t i = 0; i < arbolito.tamanio(); i++) {
        cout << numeros[i] << " ";
    }
    */
    vector<int> vect = arbolito.ancho();
    
    for(size_t i=0;i<arbolito.tamanio();i++){
        cout<<vect[i]<<endl;
    }
    

    return 0;
}

bool menor(int dato_1, int dato_2) {
    return dato_1 < dato_2;
}

bool igual(int dato_1, int dato_2) {
    return dato_1 == dato_2;
}
