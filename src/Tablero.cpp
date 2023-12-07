#include "Tablero.hpp"

using namespace std;

Tablero::Tablero() {
    matriz.resize(FILAS, vector<Casillero>(COLUMNAS, Casillero(0, VACIO)));
    grafo_tablero = Grafo(FILAS * COLUMNAS);
    enumerar();
}

void Tablero::imprimir_matriz() {
    cout << "   ";
    for (size_t i = 0; i < matriz[0].size(); i++) {
        cout << " " << i + 1 << "  ";
    }
    cout << endl;

    for (size_t i = 0; i < matriz.size(); i++) {
        if (i < 9) {
            cout << " " << i + 1 << "|";
        } else {
            cout << i + 1 << "|";
        }

        for (size_t j = 0; j < matriz[0].size(); j++) {
            cout << " " << matriz[i][j].obtener_objeto() << " |";
        }

        cout << endl;
        cout << "  +";
        for (size_t l = 0; l < matriz[0].size(); l++) {
            cout << "---+";
        }
        cout << endl;
    }
}


void Tablero::enumerar(){
    size_t contador = 0;
    for(size_t i=0;i<FILAS;i++){
        for(size_t j=0;j<COLUMNAS;j++){
            matriz[i][j] = Casillero(contador,VACIO);
            contador++;
        }
    }
}

void Tablero::asignar_objeto(size_t fila, size_t columna, string objeto) {
    if (fila >= 0 && fila < matriz.size() && columna >= 0 && columna < matriz[0].size()) {
        matriz[fila][columna].asignar_objeto(objeto);
    }
}


void Tablero::asignar_paredes(vector<size_t> casilleros){
    for(size_t i=0;i<casilleros.size();i++){
        int columna = int(casilleros[i]%9);
        int fila = int(casilleros[i]/9);
        asignar_objeto(fila,columna,PARED);
    }

}

/*
bool Tablero::busqueda_binaria(const vector<size_t>& vector_ordenado, int elemento_buscado) {
    size_t medio;
    size_t izquierda = 0;
    size_t derecha = vector_ordenado.size() - 1;
    bool encontrado = false;

    if (elemento_buscado >= 0) {
        while (izquierda <= derecha && !encontrado) {
            medio = izquierda + (derecha - izquierda) / 2;
            if (vector_ordenado[medio] == static_cast<size_t>(elemento_buscado)) {
                encontrado = true;
            } else if (vector_ordenado[medio] < static_cast<size_t>(elemento_buscado)) {
                izquierda = medio + 1;
            } else {
                derecha = medio - 1;
            }
        }
    }

    return encontrado;
}
*/

/*
void Tablero::asignar_paredes(vector<size_t> casilleros, size_t filas, size_t columnas) {
    bool encontrado;
    size_t numero_casillero;
    for (size_t i = 0; i < filas; i++) {
        for (size_t j = 0; j < columnas; j++) {
            numero_casillero = (matriz[i][j]).obtener_numero();
            encontrado = busqueda_binaria(casilleros, numero_casillero);
            if (encontrado) {
                asignar_objeto(i,j,PARED);
            }
        }
    }
}
*/

string Tablero::obtener_objeto(int vertice){
    int fila = vertice/9;
    int columna = vertice%9;

    return (matriz[fila][columna].obtener_objeto());
}

string Tablero::obtener_objeto(int fila,int columna){
    return (matriz[fila][columna].obtener_objeto());
}

int Tablero::generarEnemigos() {
    random_device rd;  // Dispositivo de generación de números aleatorios
    mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister 19937
    uniform_int_distribution<> distrib(1, 2); // Distribución uniforme entre 1 y 2

    return distrib(gen); // Devuelve 1 o 2 con igual probabilidad
}


// Se fija si la fila y la columna sean coordenadas validas dentro del tablero, si son le asigna
// el numero de casillero al vertice, y si no le asigna un valor invalido,
void Tablero::asignar_vertice(int& vertice, size_t fila, size_t columna, vector<size_t>& casilleros_especiales, bool& enemigo_alrededor) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        vertice = int((matriz[fila][columna]).obtener_numero());
    } else {
        vertice = -1;
    }

    // Solo metes al vector aquellos vertices que no sean PH y que sean validos.
    if (vertice != -1) {
        if (matriz[fila][columna].obtener_objeto() == ENEMIGO) {
            enemigo_alrededor = true;
            casilleros_especiales.push_back(static_cast<size_t>(vertice));
        }
    }
}


// Modifica el grafo si y solo si el origen y el destino son vertices validos.
void Tablero::modificar_grafo(size_t origen, int destino, size_t peso) {
    if (origen >= 0 && origen < FILAS * COLUMNAS && destino >= 0 && destino < static_cast<int>(FILAS * COLUMNAS)) {
        grafo_tablero.cambiar_arista(origen, static_cast<size_t>(destino), int(peso));
    }
}


// Aisla todos aquellos casilleros(vertices) que son un bloque ("B").
void Tablero::aislar_vertices(vector<size_t> casilleros_prohibidos) {
    size_t vertice_prohibido;
    for (size_t i = 0; i < casilleros_prohibidos.size(); i++) {
        vertice_prohibido = casilleros_prohibidos[i];
        for (size_t j = 0; j < FILAS * COLUMNAS; j++) {
            if (vertice_prohibido != j) {
                grafo_tablero.cambiar_arista(vertice_prohibido, j,INFINITO);
                grafo_tablero.cambiar_arista(j, vertice_prohibido,INFINITO);
            }
        }
    }
}


void Tablero::organizar_grafo(vector<size_t>& casilleros_bloques, bool arma_equipada) {
    size_t origen;
    int vert_izq, vert_arr, vert_der, vert_abaj;    // Pueden valer -1.
    bool enemigo_alrededor = false;
    vector<size_t> casilleros_especiales;

    for (size_t i = 0; i < FILAS; i++) {
        for (size_t j = 0; j < COLUMNAS; j++) {


            //objeto = matriz[i][j].obtener_objeto();

            // Identificamos vertices adyacentes al origen validos.
            origen = (matriz[i][j]).obtener_numero();
            asignar_vertice(vert_izq, i, j - 1, casilleros_especiales, enemigo_alrededor);
            asignar_vertice(vert_arr, i - 1, j, casilleros_especiales, enemigo_alrededor);
            asignar_vertice(vert_der, i, j + 1, casilleros_especiales, enemigo_alrededor);
            asignar_vertice(vert_abaj, i + 1, j, casilleros_especiales, enemigo_alrededor);

            if (enemigo_alrededor && !arma_equipada) {
                for (size_t k = 0; k < casilleros_especiales.size(); k++) {
                    modificar_grafo(origen,int(casilleros_especiales[k]),50);
                    //modificar_grafo(casilleros_especiales[k],static_cast<int>(origen),50);
                    modificar_grafo(casilleros_especiales[k],int(origen),50);
                }
            }

            // Unimos el origen con sus adyacentes validos.
            modificar_grafo(origen, vert_izq, 10);
            modificar_grafo(origen, vert_arr, 10);
            modificar_grafo(origen, vert_der, 10);
            modificar_grafo(origen, vert_abaj, 10);

            casilleros_especiales.clear();
            enemigo_alrededor = false;
        }
    }

    aislar_vertices(casilleros_bloques);
}

void Tablero::mostrar_camino_minimo(size_t origen, size_t destino) {
    grafo_tablero.usar_dijkstra();
    pair<vector<size_t>, int> camino_minimo = grafo_tablero.obtener_camino_minimo(origen, destino);

    // Imprimir los elementos del vector
    cout << "Camino Mínimo: ";
    for (const auto& elemento : camino_minimo.first) {
        cout << elemento << " ";
    }
    cout << endl;

    // Imprimir el entero
    cout << "Peso del Camino Mínimo: " << camino_minimo.second << endl;
}
