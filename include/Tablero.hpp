#ifndef TABLERO_H
#define TABLERO_H
#include <vector>
#include <iostream>
#include "Casillero.hpp"
#include <random>

class Tablero{
private:
    std::vector<std::vector<Casillero>> matriz;
public:
    // Constructor
    Tablero(int filas, int columnas) {
        matriz.resize(filas, std::vector<Casillero>(columnas, Casillero(0, "")));
    }

    // Mover personaje
    void moverPersonaje(size_t filaOrigen, size_t columnaOrigen, size_t filaDestino, size_t columnaDestino) {
        if (filaOrigen >= 0 && filaOrigen < matriz.size() && columnaOrigen >= 0 && columnaOrigen < matriz[0].size() &&
            filaDestino >= 0 && filaDestino < matriz.size() && columnaDestino >= 0 && columnaDestino < matriz[0].size()) {
            std::swap(matriz[filaOrigen][columnaOrigen], matriz[filaDestino][columnaDestino]);
        }
    }

    void imprimir_matriz(){
        for(int i=int(matriz.size()-1);i>=0;i--){
            for(size_t j=0;j<matriz[0].size();j++){
                std::cout<<matriz[i][j].obtener_objeto()<<"|";
            }
            std::cout<<std::endl;
            }
    }

    void enumerar(){
        int contador = 0;
        for(size_t i=0;i<matriz.size();i++){
            for(size_t j=0;j<matriz[0].size();j++){
                matriz[i][j] = Casillero(contador,"#");
                contador++;
            }
        }
    }

    void asignar_objeto(size_t fila,size_t columna,std::string valor){
        matriz[fila][columna].asignar_objeto(valor);
    }

    void asignar_paredes(std::vector<int> casilleros){
        for(size_t i=0;i<casilleros.size();i++){
            int columna = casilleros[i]%9;
            int fila = casilleros[i]/9;
            asignar_objeto(fila,columna,"\U0001f9f1")
        }
        
    }

    int generarEnemigos() {
        std::random_device rd;  // Dispositivo de generación de números aleatorios
        std::mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister 19937
        std::uniform_int_distribution<> distrib(1, 2); // Distribución uniforme entre 1 y 2

        return distrib(gen); // Devuelve 1 o 2 con igual probabilidad
}

};
#endif
