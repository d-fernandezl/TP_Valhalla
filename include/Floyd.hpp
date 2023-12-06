#ifndef GRAFOS_FLOYD_H
#define GRAFOS_FLOYD_H

#include "CaminoMinimo.hpp"

class Floyd : public CaminoMinimo {
private:
    Matriz matriz_costos;
    Matriz matriz_caminos;

    // Pre: -
    // Post: Inicializa las matrices de costos y caminos necesarias para el algoritmo.
    void inicializar_matrices();

    // Pre: Se deben haber calculado las matrices.
    // Post: Devuelve el camino desde origen a destino.
    std::vector<size_t> obtener_camino(size_t origen, size_t destino);

    // Pre: -
    // Post: Devuelve el vector_original en reversa.
    std::vector<size_t> reverse_vector(std::vector<size_t> vector_original);

public:
    // Constructor.
    Floyd();

    std::vector<size_t>
    calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino,
                           bool hay_cambios) override;

    ~Floyd() override;
};

#endif
