#ifndef CASILLERO_H
#define CASILLERO_H
#include <iostream>


class Casillero{
private:
    int numero;
    std::string objeto;
public:
    //Constructor
    Casillero(int numero,std::string objeto);

    //Pre: -
    //Post: Devuelve el dato.
    std::string obtener_objeto();

    void asignar_objeto(std::string objeto);

    //Pre: -
    //Post:Devuelve el vertice.
    int obtener_numero();
};

#endif