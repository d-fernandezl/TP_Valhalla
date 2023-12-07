#ifndef JUGADOR_H
#define JUGADOR_H

#include "Inventario.hpp"
#include "ABBv2.hpp"
//#include "Placa.hpp"
//#include "Arma.hpp"
//#include "Casillero.hpp"
#include "Tablero.hpp"
//#include "Menu.hpp"

const int COTA_INFERIOR = 0;
const int COTA_SUPERIOR = 8;

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
class Jugador{
private:
    Inventario<A,comp> inventario_armas = Inventario<Arma,comp>();
    ABB<P,menor,igual> arbol_placas = ABB<P,menor,igual>();
    bool arma_activa;
    int fila;
    int columna;
    size_t puntos;
public:
    //Constructor
    Jugador(int fila,int columna,bool arma_activa);

    //Pre: Recibe un caracter
    //Post: Mueve el jugador por el tablero segun el caracter
    void mover_jugador(std::string mov,Tablero& matriz);
    
    //Pre: Ingrasa el movimiento que va a hacer.
    //Post:Devuelve true si ese movimiento es posible.
    bool movimiento_permitido(int movimiento_x,int movimiento_y,Tablero& matriz);
    
    void volver_al_inicio(Tablero& matriz);

    //Pre:
    //Post: Devuelve la fila en la que se encuentra el jugador.
    int obtener_fila();

    //Pre:
    //Post: Devuelve la columna en la que se encuentra el jugador.
    int obtener_columna();
    //Pre:
    //Post:
    bool arma_esta_activa();

    //Pre:
    //Post: Devuelve la altura del arbol
    size_t altura_del_arbol();

    void agarrar_placa(P nueva_placa);

    //Pre:
    //Post: Devuelve los puntos del jugador.
    size_t obtener_puntos();

};

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
Jugador<A,P,comp,menor,igual>::Jugador(int fila,int columna,bool arma_activa){
    this->fila = fila;
    this->columna = columna;
    this->arma_activa = arma_activa;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Jugador<A,P,comp,menor,igual>::mover_jugador(std::string mov,Tablero& matriz){
    int movimiento_x = 0;
    int movimiento_y = 0;
    if(mov=="w" || mov=="W"){
        movimiento_y = -1;
    }
    else if(mov=="s" || mov=="S"){
        movimiento_y = 1;
    }
    else if(mov=="a" || mov=="A"){
        movimiento_x = -1;
    }
    else if(mov=="d" || mov=="D"){
        movimiento_x = 1;
    }
    
    if (movimiento_permitido(columna+movimiento_x,fila+movimiento_y,matriz)){
        int nueva_fila = (fila+movimiento_y);
        int nueva_columna = (columna+movimiento_x);
        matriz.asignar_objeto(nueva_fila,nueva_columna,JUGADOR);
        matriz.asignar_objeto(fila,columna,VACIO);
        fila = nueva_fila;
        columna = nueva_columna;
    }
    std::cout<<"X:"<<columna<<std::endl;
    std::cout<<"Y:"<<fila<<std::endl;
     
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
bool Jugador<A,P,comp,menor,igual>::movimiento_permitido(int movimiento_x,int movimiento_y,Tablero& matriz){
    return movimiento_x>=COTA_INFERIOR && movimiento_x<=COTA_SUPERIOR && movimiento_y>=COTA_INFERIOR && movimiento_y<=COTA_SUPERIOR && (matriz.obtener_objeto(movimiento_y,movimiento_x)==VACIO || (matriz.obtener_objeto(movimiento_y,movimiento_x)==ENEMIGO && arma_activa==true));
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
int Jugador<A,P,comp,menor,igual>::obtener_fila(){
    return fila;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
int Jugador<A,P,comp,menor,igual>::obtener_columna(){
    return columna;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
bool Jugador<A,P,comp,menor,igual>::arma_esta_activa(){
    return arma_activa;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
size_t Jugador<A,P,comp,menor,igual>::altura_del_arbol(){
    return arbol_placas.altura();
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
size_t Jugador<A,P,comp,menor,igual>::obtener_puntos(){
    return puntos;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Jugador<A,P,comp,menor,igual>::volver_al_inicio(Tablero& matriz){
    matriz.asignar_objeto(fila,columna,VACIO);
    this->fila=8;
    this->columna=0;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Jugador<A,P,comp,menor,igual>::agarrar_placa(P nueva_placa){
    arbol_placas.alta(nueva_placa);
}

#endif
