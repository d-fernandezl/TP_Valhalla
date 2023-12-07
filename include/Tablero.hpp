#ifndef TABLERO_H
#define TABLERO_H
#include <vector>
#include <iostream>
#include "Casillero.hpp"
#include <random>

const std::string JUGADOR="\U0001f935";//J
const std::string PARED="\U0001f9f1";//B
const std::string ENEMIGO="\U0001f480";//P
const std::string VACIO=".";
const std::string MULTIPLICADOR="\U00002b"; //+

struct Lugar {
    int fila;
    int columna;
};

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


    std::string obtener_objeto(int vertice){
            int fila = vertice/9;
            int columna = vertice%9;
    
            return (matriz[fila][columna].obtener_objeto());
    }

void asignar_objeto(int fila, int columna, const std::string& objeto) {
    matriz[fila][columna].asignar_objeto(objeto);
}

//para el pyramid head

// Genera enemigos en posiciones aleatorias que no sean paredes
/*
*generar_Lugar_Aleatorio() genera una posicion aleatoria en el tablero que no sea una pared. 
Crea un objeto lugar de la clase lugar y asigna a lugar.fila y lugar.columna,con lo cual los valores aleatorios que se representan una posición valida en el tablero.
*La funcion generarEnemigos() utiliza la clase Lugar para generar enemigos en posiciones aleatorias en el tablero que no sean paredes. 
*generarPosicionAleatoria() asigna un enemigo a esa posicion en el tablero ya sea 0, 1 o 2.

*/
    int generar_Enemigos() {
        std::random_device rd; 
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2); 
        int numEnemigos = distrib(gen);
        for (int i = 0; i < numEnemigos; i++) {
            Lugar lugar = generar_Lugar_Aleatorio();
            matriz[lugar.fila][lugar.columna].asignar_objeto(ENEMIGO);
        }
        return numEnemigos;
    }

    void generar_Multiplicador() {
        Lugar lugar = generar_Lugar_Aleatorio();
        matriz[lugar.fila][lugar.columna].asignar_objeto(MULTIPLICADOR);
    }
};

    Lugar generar_Lugar_Aleatorio() {
        std::random_device rd;
        std::mt19937 gen(rd());
        Lugar lugar;
        do {
            std::uniform_int_distribution<> distribFila(0, matriz.size() - 1);
            std::uniform_int_distribution<> distribColumna(0, matriz[0].size() - 1);
            lugar.fila = distribFila(gen);
            lugar.columna = distribColumna(gen);
        } while (matriz[lugar.fila][lugar.columna].obtener_objeto() == PARED); 
        return lugar;
    }
};
#endif
