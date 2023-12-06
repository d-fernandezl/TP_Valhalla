#ifndef TABLERO_H
#define TABLERO_H
#include <vector>
#include <iostream>
#include "Casillero.hpp"
#include <random>

const std::string JUGADOR="J";
const std::string PARED="B";
const std::string ENEMIGO="P";
const std::string VACIO=".";

class Tablero{
private:
    std::vector<std::vector<Casillero>> matriz;
Grafo grafo_tablero();
public:
    // Constructor
    Tablero(int filas, int columnas) {
        matriz.resize(filas, std::vector<Casillero>(columnas, Casillero(0, "")));
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
                matriz[i][j] = Casillero(contador,VACIO);
                contador++;
            }
        }
    }

    void asignar_paredes(std::vector<int> casilleros){
        for(size_t i=0;i<casilleros.size();i++){
            int columna = casilleros[i]%9;
            int fila = casilleros[i]/9;
            asignar_objeto(fila,columna,PARED);
        }
        
    }

    int generarEnemigos() {
        std::random_device rd;  // Dispositivo de generación de números aleatorios
        std::mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister 19937
        std::uniform_int_distribution<> distrib(1, 2); // Distribución uniforme entre 1 y 2

        return distrib(gen); // Devuelve 1 o 2 con igual probabilidad
}
    std::string obtener_objeto(int vertice){
            int fila = vertice/9;
            int columna = vertice%9;
    
            return (matriz[fila][columna].obtener_objeto());
    }
//para el pyramid head

// Genera enemigos en posiciones aleatorias que no sean paredes
/*
*generar_Lugar_Aleatorio() genera una posicion aleatoria en el tablero que no sea una pared. 
Crea un objeto lugar de la clase lugar y asigna a lugar.fila y lugar.columna,con lo cual los valores aleatorios que se representan una posición valida en el tablero.
*La funcion generarEnemigos() utiliza la clase Lugar para generar enemigos en posiciones aleatorias en el tablero que no sean paredes. 
*generarPosicionAleatoria() asigna un enemigo a esa posicion en el tablero ya sea 0, 1 o 2.

*/
    int generarEnemigos() {
        std::random_device rd; // genera numeros aleatorios
        std::mt19937 gen(rd());// genera numeros aleatorios en Mersenne Twister 19937
        std::uniform_int_distribution<> distrib(0, 2); // Distribucion de entre 0, 1 y 2
        int numEnemigos = distrib(gen);
        for (int i = 0; i < numEnemigos; i++) {
            Lugar lugar = generar_Lugar_Aleatorio();
            matriz[lugar.fila][lugar.columna].asignar_objeto("E");
        }
        return numEnemigos;
    }

    Lugar generar_Lugar_Aleatorio() {
        std::random_device rd;
        std::mt19937 gen(rd());
        Lugar lugar;
        do {
            std::uniform_int_distribution<> distribFila(0, matriz.size() - 1);
            std::uniform_int_distribution<> distribColumna(0, matriz[0].size() - 1);
            lugar.fila = distribFila(gen);
            lugar.columna = distribColumna(gen);
        } while (matriz[lugar.fila][lugar.columna].obtener_objeto() == "p"); // Si es una pared, generar otra posición
        return lugar;
    }
};
#endif
