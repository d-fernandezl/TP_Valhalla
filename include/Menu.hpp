#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Juego.hpp"  
#include "Jugador.hpp" 
#include "Arma.hpp"  
#include "Dijkstra.hpp" 

class Menu {
public:
    // Constructor
    Menu(Juego& juego);

   
    void mostrar_menu();

private:
    Juego& juego;  

    
    void mostrar_puntos_jugador();
    void mostrar_nivel_arma();
    void mostrar_existencia_arma();
    void mostrar_cantidad_enemigos();
    void mostrar_camino_minimo();
};

#endif
