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

std::vector<size_t> Floyd::reverse_vector(std::vector<size_t> vector_original) {
    std::vector<size_t> vector_en_reversa;
    size_t tamanio_vector_original = vector_original.size();
    for (size_t i = 0; i < tamanio_vector_original; i++) {
        vector_en_reversa.push_back(vector_original[tamanio_vector_original - i - 1]);
    }
    return vector_en_reversa;
}

std::vector<size_t> Floyd::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;

    camino.push_back(destino);
    if (origen != destino) {
        while (matriz_caminos.elemento(origen, destino) != destino) {
            camino.push_back(matriz_caminos.elemento(origen, destino));
            destino = matriz_caminos.elemento(origen, destino);
        }
        camino.push_back(origen);
        camino = reverse_vector(camino);
    }

    return camino;
}

std::vector<size_t>
Floyd::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) {
    if (hay_cambios) {
        matriz_adyacencia = adyacencia;
        cantidad_vertices = vertices;
        inicializar_matrices();

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
                            matriz_caminos.elemento(i,j) = int(k);
                        }
                    }
                }
            }
        }
    }
    
    return obtener_camino(origen, destino);
}

Floyd::~Floyd() {}
