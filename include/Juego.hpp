#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.hpp"
#include "Jugador.hpp"
#include "Arma.hpp"
#include "Placa.hpp"

const size_t RONDAS_MAXIMAS = 5;

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>

class Juego{// el juego se ejecuta hasta que el jugador pierda o gane
private:
    size_t rondas;
    Jugador<comp,menor,igual> player;
    Tablero tablero;
public:
    //Constructor
    Juego();

    //Pre: -
    //Post: Inicia el juego.
    void iniciar_juego();
    
};

#endif
