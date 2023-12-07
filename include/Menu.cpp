#include "Menu.hpp"
#include <iostream>

Menu::Menu(Juego& juego) : juego(juego) {}

void Menu::mostrar_menu() {
    bool activo = true;

    while (activo) {
        size_t opcion;

        std::cout << "Menu:" << std::endl;
        std::cout << "1. Mover al jugador" << std::endl;
        std::cout << "2. Mostrar puntos del jugador" << std::endl;
        std::cout << "3. Mostrar nivel del arma" << std::endl;
        std::cout << "4. Ver si tienes un arma" << std::endl;
        std::cout << "5. Contar enemigos" << std::endl;
        std::cout << "6. Mostrar camino mínimo" << std::endl;
        std::cout << "7. Salir del juego" << std::endl;

        std::cout << "Ingrese la opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                juego.mover_jugador();
                break;

            case 2:
                
                mostrar_puntos_jugador();
                break;

            case 3:
                
                mostrar_nivel_arma();
                break;

            case 4:
            
                mostrar_existencia_arma();
                break;

            case 5:
                mostrar_cantidad_enemigos();
                break;

            case 6:
               
                mostrar_camino_minimo();
                break;

            case 7:
                // Salir del juego
                activo = false;
                std::cout << "Juego perdido" << std::endl;
                break;

            default:
                std::cout << "Opción no válida. Inténtelo de nuevo." << std::endl;
                break;
        }
    }
}

void Menu::mostrar_puntos_jugador() {
   
    std::cout << "Puntos del jugador: " << juego.obtener_puntos_jugador() << std::endl;
}

void Menu::mostrar_nivel_arma() {
   
    std::cout << "Nivel del arma: " << juego.obtener_nivel_arma() << std::endl;
}

void Menu::mostrar_existencia_arma() {
    if (juego.tiene_arma()) {
        std::cout << "Tienes un arma." << std::endl;
    } else {
        std::cout << "No tienes un arma." << std::endl;
    }
}

void Menu::mostrar_cantidad_enemigos() {
    
    std::cout << "Cantidad de enemigos: " << juego.contar_enemigos() << std::endl;
}

void Menu::mostrar_camino_minimo() {
    juego.mostrar_camino_minimo();
}
