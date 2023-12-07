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

    void cargar_datos(std::string ruta_archivo, std::vector<std::string>& datos);
    size_t generar_numero_aleatorio_unico(size_t min, size_t max);
    size_t generar_numero_aleatorio(size_t min, size_t max);
    std::string obtener_leyenda();
    Placa* generar_placa_aleatoria();

    Arma generar_arma_aleatoria();


public:
    Aleatorio();
    void cargar_placa_aleatoria(ABB<Placa*, Placa::menor, Placa::igual> &Arbol);
    void obtener_arma_aleatoria(Inventario<Arma, comp> &inventario_armas);
    ~Aleatorio();

    //void verificar();
};



#endif