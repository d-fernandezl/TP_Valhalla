#include <iostream>
#include "Tablero.hpp"
#include "Jugador.hpp"

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
class Menu {
private:
    Jugador<comp,menor,igual> player;

public:

    // Constructor
    Menu(int posicion_inicial, bool arma_activa) : player(posicion_inicial, arma_activa) {}

    // Muestra la cantidad de enemigos generados
    void mostrar_cantidad_enemigos_aparecidos(Tablero& tablero);

    // Muestra si el jugador tiene un arma o no
    void mostrar_estado_arma();

    // Muestra el camino mínimo
    void mostrar_camino_minimo(Tablero& tablero);

    // Muestra el menú principal
    void mostrar_menu(Tablero& tablero_juego);
};

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
void Menu<comp,menor,igual>::mostrar_cantidad_enemigos_aparecidos(Tablero& tablero) {
    int cantidadEnemigos = tablero.generar_Enemigos();
    std::cout << "Se han generado " << cantidadEnemigos << " enemigos." << std::endl;
}

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
void Menu<comp,menor,igual>::mostrar_estado_arma() {
    if (player.tiene_arma()) {
        std::cout << "El jugador tiene un arma." << std::endl;
    } else {
        std::cout << "El jugador no tiene un arma." << std::endl;
    }
}

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
void Menu<comp,menor,igual>::mostrar_camino_minimo(Tablero& tablero) {
    
    size_t origen = player.obtener_posicion();
    size_t destino; 

    // Utilizar la clase Dijkstra  método de camino mínimo 
    Dijkstra dijkstra;
    std::vector<size_t> camino = dijkstra.calcular_camino_minimo(tablero.grafo_tablero(), tablero.obtener_cantidad_vertices(), origen, destino, false);

    
    std::cout << "Camino mínimo: ";
    for (size_t vertice : camino) {
        std::cout << vertice << " ";
    }
    std::cout << std::endl;
}

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
void Menu<comp,menor,igual>::mostrar_menu(Tablero& tablero_juego) {
    bool activo = true;

    while (activo) {
        size_t opcion;
        std::cout << "Ingrese la opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: {
                std::string movimiento;
                std::cout << "Ingrese el movimiento (w, a, s, d): ";
                std::cin >> movimiento;
                player.mover_jugador(movimiento, tablero_juego);
                break;
            }
            case 4: {
                
                mostrar_estado_arma();
                break;
            }
            case 6: {
                
                mostrar_camino_minimo(tablero_juego);
                break;
            }
            case 7: {
                mostrar_cantidad_enemigos_aparecidos(tablero_juego);
                break;
            }
            case 0: {
                activo = false;
                std::cout << "Juego perdido" << std::endl;
                break;
            }
            default: {
                std::cout << "Opción no válida. Inténtelo de nuevo." << std::endl;
                break;
            }
        }
    }
}
