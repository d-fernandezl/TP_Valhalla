#ifndef ALEATORIO_HPP
#define ALEATORIO_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "ABBv2.hpp"
#include "Placa.hpp"
#include "Arma.hpp"
#include "Inventario.hpp"

// Pre: arma_1 y arma_2 deben ser objetos Arma validos.
// Post: Se devuelve true si arma_1 es mayor que arma_2, false en caso contrario.
bool comp(Arma arma_1, Arma arma_2);

class Aleatorio {
private:
    const size_t ID_MINIMO = 100;
    const size_t ID_MAXIMO = 666;
    const size_t POTENCIA_MINIMA = 10;
    const size_t POTENCIA_MAXIMO = 100;
    const size_t SUERTE = 1;
    const std::vector<size_t> VECTOR_BOOLEANO = {0, 0, 0, 0, 1};


    std::vector<size_t> numeros_generados;
    std::vector<std::string> leyendas;
    std::vector<std::string> armas;

    size_t contador;


    // Pre: ruta_archivo tiene que ser una ruta valida a un archivo y tiene que recibir un vector de strings.
    // Post: Se cargar los datos del archivo en el vector 'datos'
    void cargar_datos(std::string ruta_archivo, std::vector<std::string>& datos);

    // Pre: 'min' tiene que ser menor o igual que 'max', dichos parametros tiene que ser UNICAMENTE numero positivos.
    // Post: Se generara un numero aleatorio unico entre los valores que se reciba de 'min' y 'max', y se agregara al vector 'numeros_generados'.
    size_t generar_numero_aleatorio_unico(size_t min, size_t max);

    // Pre: min' tiene que ser menor o igual que 'max', dichos parametros tiene que ser UNICAMENTE numero positivos.
    // Post: Se generara un numero aleatorio entre los valores que se reciba de 'min' y 'max'
    size_t generar_numero_aleatorio(size_t min, size_t max);

    // Pre: El vector 'leyendas' tiene que estar inicializado.
    // Post: Se devolvera una leyenda del vector leyendas y se incrementara ''contador'.
    std::string obtener_leyenda();

    // Pre: -
    // Post: Se generara una placa aleatoria y se devolvera un puntero a ella.
    Placa* generar_placa_aleatoria();

    // Pre: El vector 'armas' tiene que estar inicializado.
    // Post: Se generara un arma aleatoria posteriormente es devuelta.
    Arma generar_arma_aleatoria();


public:

    // Constructor
    // Pre: -
    // Post: Se iniciliza el objeto 'Aleatorio' y se cargan los datos de los archivos
    // 'ARCHIVO_LEYENDAS' y 'ARCHIVO_ARMAS' en los vectores leyendas y armas respectivamente.
    Aleatorio();

    // Pre: 'Arbol' tiene que se un arbol binario de busqueda valido.
    // Post: Se creara una placa aleatoria y se agrega al arbol 'Arbol'.
    void cargar_placa_aleatoria(ABB<Placa*, Placa::menor, Placa::igual> &Arbol);

    // Pre: 'inventario_armas' debe ser un inventario valido.
    // Post: Si hay armas disponibles y se cumple la condicion de suerte, se genera un arma aleatoria y se
    // agrega al inventario 'inventario_armas'.
    void obtener_arma_aleatoria(Inventario<Arma, comp> &inventario_armas);

    // Destructor
    ~Aleatorio();

};



#endif