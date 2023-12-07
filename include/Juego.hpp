#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.hpp"
#include "Jugador.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>

const size_t RONDAS_MAXIMAS = 5;

//template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>

class Juego{// el juego se ejecuta hasta que el jugador pierda o gane
private:
    size_t rondas;
    Jugador<A,P,comp,menor,igual> player = Jugador<A,P,comp,menor,igual>(8,0,false);
    Tablero tablero;
    Menu<A,P,comp,menor,igual> menu;
public:
    //Constructor
    Juego();

    //Pre: -
    //Post: Inicia el juego.
    void iniciar_juego();
    
};

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
Juego<A,P,comp,menor,igual>::Juego(){
    tablero = Tablero();
    rondas = 1;
    menu = Menu<A,P,comp,menor,igual>();
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Juego<A,P,comp,menor,igual>::iniciar_juego(){
    bool partida_activa = true;
    size_t altura = player.altura_del_arbol();

    while(partida_activa){ // Faltaria agregar que mientras sea posible llegar a la salida
        //Verifica la altura del arbol de placas arbol de placas
        //size_t altura = player.altura_del_arbol();
        /*
        layout = {1, 3, 5, 7, 10, 14, 16, 19, 21, 23, 30, 32, 34, 37,
                                         39, 43, 46, 50, 52, 55, 57, 59, 61, 66, 68, 70, 75};
        */
       std::cout<<"Nivel "<<rondas<<std::endl;
        std::vector<size_t> layout;
        if(altura%2==0){
            layout = {1, 3, 5, 7, 10, 14, 16, 19, 21, 23, 30, 32, 34, 37,
                                         39, 43, 46, 50, 52, 55, 57, 59, 61, 66, 68, 70, 75};
        }else{
            layout = {10,11,12,13,14,
            16,25,27,28,30,31,32,43,46,47,48,50,52,59,64,66,68,70,71,75}; // falta las paredes del layout 2
        }
        tablero.asignar_paredes(layout);
        tablero.asignar_objeto(8, 0, JUGADOR);
        bool finalizado=false;
        while(!finalizado){
            tablero.imprimir_matriz();
            menu.mostrar_menu(player,tablero);
            if(player.obtener_fila()==0 && player.obtener_columna()==8 && rondas<RONDAS_MAXIMAS){
                std::cout<<"Pasastes el nivel"<<std::endl;
                finalizado=true;
                player.volver_al_inicio(tablero);
                altura++;
                tablero = Tablero();
            }else if(player.obtener_fila()==0 && player.obtener_columna()==8 && rondas==RONDAS_MAXIMAS){
                finalizado=true;
                partida_activa = false;
                std::cout<<"Felicidades has ganado el juego. Esta vez"<<std::endl;
            }
        }
        rondas++;
    }
}

#endif
