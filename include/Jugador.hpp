#ifndef JUGADOR_H
#define JUGADOR_H

#include "Inventario.hpp"
#include "ABBv2.hpp"
#include "Placa.hpp"
#include "Arma.hpp"
#include "Casillero.hpp"
#include "Tablero.hpp"

const int COTA_INFERIOR = 0;
const int COTA_SUPERIOR = 80;

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
class Jugador{
private:
    Inventario<Arma,comp> inventario_armas();
    ABB<Placa,menor,igual> arbol_placas();
    bool arma_activa;
    int posicion;
public:
    //Constructor
    Jugador(int posicion,bool arma_activa);

    //Pre: Recibe un caracter
    //Post: Mueve el jugador por el tablero segun el caracter
    void mover_jugador(std::string mov,Tablero& matriz);
    
    //Pre: Ingrasa el movimiento que va a hacer.
    //Post:Devuelve true si ese movimiento es posible.
    bool movimiento_permitido(int movimiento,Tablero& matriz);
    
    //Pre:
    //Post:Devuelve la posicion del jugador
    int obtener_posicion();
};

//template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
//Jugador<comp,menor,igual>::

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
Jugador<comp,menor,igual>::Jugador(int posicion,bool arma_activa){
    this->posicion=posicion;
    this->arma_activa=arma_activa;
}

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
void Jugador<comp,menor,igual>::mover_jugador(std::string mov,Tablero& matriz){
    int movimiento = 0;
    if(mov=="w" || mov=="W"){
        movimiento = 9;
    }
    else if(mov=="s" || mov=="S"){
        movimiento = -9;
    }
    else if(mov=="a" || mov=="A"){
        movimiento = -1;
    }
    else if(mov=="d" || mov=="D"){
        movimiento = 1;
    }
    if (movimiento_permitido(movimiento,matriz)){
        int nueva_fila = (posicion+movimiento)/9;
        int nueva_columna = (posicion+movimiento)%9;
        matriz.asignar_objeto(nueva_fila,nueva_columna,JUGADOR);
        int anterior_fila = (posicion)/9;
        int anterior_columna = (posicion)%9;
        matriz.asignar_objeto(anterior_fila,anterior_columna,VACIO);
        posicion = posicion+movimiento;
    }
}

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
bool Jugador<comp,menor,igual>::movimiento_permitido(int movimiento,Tablero& matriz){
    int new_posicion = posicion+movimiento;
    if(new_posicion>=COTA_INFERIOR && new_posicion<=COTA_SUPERIOR && matriz.obtener_objeto(new_posicion)=="."){
            return true;
    }
    return false;
}
template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
int Jugador<comp,menor,igual>::obtener_posicion(){
    return posicion;
}

#endif
