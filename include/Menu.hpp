#include <iostream>
#include "Tablero.hpp"
#include "Jugador.hpp"
#include "Dijkstra.hpp"

const size_t CANTIDAD_VERTICES = 81;

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
class Menu {
private:

    void mover_player(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego);
public:

    // Constructor
    Menu(){}

    // Muestra la cantidad de enemigos generados
    void mostrar_cantidad_enemigos_aparecidos(Tablero& tablero);

    // Muestra si el jugador tiene un arma o no
    void mostrar_estado_arma(Jugador<A,P,comp,menor,igual>& player);

    // Muestra el camino minimo
    void mostrar_camino_minimo(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero);

    // Muestra el menu principal
    void mostrar_menu(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego);
};

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mostrar_cantidad_enemigos_aparecidos(Tablero& tablero) {
    int cantidadEnemigos = tablero.generarEnemigos();
    std::cout << "Se han generado " << cantidadEnemigos << " Pyramid Head." << std::endl;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mostrar_estado_arma(Jugador<A,P,comp,menor,igual>& player) {
    if (player.tiene_arma()) {
        std::cout << "Tengo un arma." << std::endl;
    } else {
        std::cout << "Oh no, no tengo arma." << std::endl;
    }
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mostrar_camino_minimo(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero) {
    
    size_t origen = player.obtener_posicion(tablero);
    size_t destino = 80; 

    // Utilizar la clase Dijkstra  metodo de camino minimo 
    Dijkstra dijkstra;
    //std::vector<size_t> camino = dijkstra.calcular_camino_minimo(tablero.grafo_tablero, CANTIDAD_VERTICES, origen, destino, false);
    Grafo grafito = tablero.obtener_grafo();
    grafito.usar_dijkstra();
    std::pair<std::vector<size_t>, int> camino = grafito.obtener_camino_minimo(origen,destino);

    std::vector<size_t> camino_minimo = camino.first;
    
    std::cout << "Camino minimo: ";
    for (size_t vertice : camino_minimo) {
        std::cout << vertice << " ";
    }
    std::cout << std::endl;
}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mostrar_menu(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego) {
    //bool activo = true;
    std::cout << "1: Mover al jugador." << std::endl;
    std::cout << "2: Verificar si el jugador tiene un arma." << std::endl;
    std::cout << "3: Mostrar el camino minimo." << std::endl;
    std::cout << "4: Mostrar la cantidad de enemigos generados." << std::endl;
    std::cout << "0: Terminar el juego." << std::endl;

    size_t opcion;
    std::cout << "Ingrese la opcion: ";
    std::cin >> opcion;

    switch(opcion) {
    case 1: {
        mover_player(player,tablero_juego);
        break;
    }
    case 2: {
        
        if(player.tiene_arma()){
            std::cout<<"El jugador esta armado"<<std::endl;
        }else{
            std::cout<<"El jugador esta desarmado"<<std::endl;
        }
        break;
    }
    case 3: { 
        mostrar_camino_minimo(player,tablero_juego);
        break;
    }
    case 4: {
        
        mostrar_cantidad_enemigos_aparecidos(tablero_juego);
        break;
    }
    case 0: {
        activo = false;
        std::cout << "Tu has muerto" << std::endl;
        break;
    }
    default: {
        std::cout << "Opcion no invalida. Oprima otra opcion." << std::endl;
        break;
    }
}

}

template<typename A,typename P,bool comp(A,A),bool menor(P,P),bool igual(P,P)>
void Menu<A,P,comp,menor,igual>::mover_player(Jugador<A,P,comp,menor,igual>& player,Tablero& tablero_juego){
    std::string movimiento;
    std::cout << "Movimientos para el personaje (w, a, s, d): ";
    std::cin >> movimiento;
    player.mover_jugador(movimiento, tablero_juego);
}