#include "Floyd.hpp"

Floyd::Floyd() {}

void Floyd::inicializar_matrices() {
    matriz_caminos = Matriz(cantidad_vertices);
    for (size_t i = 0; i < cantidad_vertices; i++) {
        for (size_t j = 0; j < cantidad_vertices; j++) {
            matriz_caminos.elemento(i, j) = (int) j;
        }
    }

    matriz_costos = matriz_adyacencia;
}

std::vector<size_t> Floyd::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;

    // TODO: Escribir el código necesario, haciendo uso de los métodos existentes.

    return camino;
}

std::vector<size_t>
Floyd::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) {
    if (hay_cambios) {
        matriz_adyacencia = adyacencia;
        cantidad_vertices = vertices;
        inicializar_matrices();

        // TODO: Escribir el código necesario, haciendo uso de los métodos existentes.
        for(size_t k = 0;k<cantidad_vertices;k++){ // K es tanto fila como columna
            for(size_t i = 0;i<cantidad_vertices;i++){ //i se usa como fila
                for(size_t j=0;j<cantidad_vertices;j++){ //j se usa como columna
                    if(k!=i && k!=j){
                        int dato1 = matriz_adyacencia.elemento(i,j);
                        int dato2 = matriz_adyacencia.elemento(k,j) + matriz_adyacencia.elemento(i,k);
                        if(dato1<dato2){
                            matriz_adyacencia.elemento(i,j) = dato1; // elemento(i,j) es la esquina opuesta al k (o opuesta a la diagonal).
                        }else{
                            matriz_adyacencia.elemento(i,j) = dato2;// Falta que cambie tambien en la matriz de caminos.
                            matriz_caminos.elemento(i,j) = matriz_caminos.elemento(k,j);
                        }
                    }
                }
            }
        }
    }
    
    return obtener_camino(origen, destino);
}

Floyd::~Floyd() {}