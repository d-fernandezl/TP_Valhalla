#ifndef TABLERO_H
#define TABLERO_H
//#include <vector>
#include <iostream>
#include "Casillero.hpp"
#include <random>
#include "Grafo.hpp"

const std::string JUGADOR = "J";
const std::string PARED = "B";
const std::string ENEMIGO = "P";
const std::string VACIO = " ";

const size_t FILAS = 9;
const size_t COLUMNAS = 9;

class Tablero{
private:
    std::vector<std::vector<Casillero>> matriz;
    Grafo grafo_tablero;

    void enumerar();
public:
    // Constructor
    Tablero();

    void imprimir_matriz();

    void asignar_objeto(size_t fila, size_t columna, std::string objeto);

    //bool busqueda_binaria(const std::vector<size_t>& vector_ordenado, int elemento_buscado);

    void asignar_paredes(std::vector<size_t> casilleros);

    // No funciona
    //void asignar_paredes(std::vector<size_t> casilleros, size_t fila, size_t columnas);

    std::string obtener_objeto(int vertice);

    std::string obtener_objeto(int fila,int columna);

    int generarEnemigos();

    void organizar_grafo(std::vector<size_t>& casilleros_bloques, bool arma_equipada);

    void asignar_vertice(int& vertice, size_t fila, size_t columna, std::vector<size_t>& casilleros_especiales, bool& enemigo_alrededor);

    void modificar_grafo(size_t origen, int destino, size_t peso);

    void aislar_vertices(std::vector<size_t> casilleros_prohibidos);

    void mostrar_camino_minimo(size_t origen, size_t destino);

};

#endif
