#ifndef MENU_H
#define MENU_H
#include <iostream>

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
class Menu{
private:
    void mover_player(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego);
public:
    //Constructor
    Menu();

    void mostrar_menu(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego);

};

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
Menu<A,P,comp,menor,igual>::Menu(){}


template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mostrar_menu(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego){
    std::cout<<"1-Mover al jugador"<<std::endl;
    std::cout<<"2-Tamanio del arbol"<<std::endl;
    size_t opcion = 0;
    std::cin>>opcion;

    switch(opcion)
    {
    case 1:
        mover_player(player,tablero_juego);
        break;
    case 2:
        std::cout<<"La altura del arbol es:"<<player.altura_del_arbol()<<std::endl;
        break;
    default:
        break;
    }
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mover_player(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego){
    std::cout<<"Ingresa 5-(w) 2-(s) 1-(a) 3-(d) para moverte"<<std::endl;
     size_t opcion1 = 0;
     std::string opcionstr = "";
     std::cin>>opcion1;
     switch (opcion1)
     {
     case 5:
         opcionstr = "w";
         break;
     case 2:
         opcionstr = "s";
         break;
     case 1:
         opcionstr = "a";
         break;
     case 3:
         opcionstr = "d";
         break;
     default:
         break;
     }
    player.mover_jugador(opcionstr,tablero_juego);
}

#endif
