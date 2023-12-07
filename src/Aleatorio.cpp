#include "Aleatorio.hpp"

using namespace std;

const string ARCHIVO_LEYENDAS = "./Leyendas.txt";
const string ARCHIVO_ARMAS = "./Armas.txt";

Aleatorio::Aleatorio() {

    this -> contador = 0;
    cargar_datos(ARCHIVO_LEYENDAS, leyendas);
    cargar_datos(ARCHIVO_ARMAS, armas);
}

void Aleatorio::cargar_datos(string ruta_archivo, vector<std::string>& datos) {
    ifstream archivo(ruta_archivo);
    string linea;

    if(!archivo.is_open()) {
        cout << "No se ha podido abrir correctamente el archivo." << endl;
        return;
    } else {
        while(getline(archivo, linea)){
            datos.push_back(linea);
        }
    }
    archivo.close();
}

size_t Aleatorio::generar_numero_aleatorio_unico(size_t min, size_t max) {
    size_t numero = 0;
    do{
        srand(static_cast<unsigned int>(time(0)));
        numero = static_cast<size_t>(rand()) % (max + 1  - min) + min;
    } while(find(numeros_generados.begin(), numeros_generados.end(), numero) != numeros_generados.end());

    numeros_generados.push_back(numero);

    return static_cast<size_t>(numero);
}

std::string Aleatorio::obtener_leyenda() {
    string leyenda;

    if(contador < leyendas.size()){
        leyenda = leyendas[contador];
        contador++;
    } else{
        contador = 0;
        leyenda = leyendas[contador];
    }
    return leyenda;
}

Placa *Aleatorio::generar_placa_aleatoria() {
    size_t id = generar_numero_aleatorio_unico(ID_MINIMO, ID_MAXIMO);
    string leyenda = obtener_leyenda();
    Placa* placa = new Placa("Linea", leyenda, static_cast<int>(id));
    return placa;
}

void Aleatorio::cargar_placa_aleatoria(ABB<Placa *, Placa::menor, Placa::igual> &Arbol) {
    Placa* placa = generar_placa_aleatoria();
    Arbol.alta(placa);
}

size_t Aleatorio::generar_numero_aleatorio(size_t min, size_t max) {
    return static_cast<size_t>(rand()) % (max + 1  - min) + min;
}

Arma Aleatorio::generar_arma_aleatoria() {
    size_t potencia = generar_numero_aleatorio(POTENCIA_MINIMA, POTENCIA_MAXIMO);
    size_t indice = generar_numero_aleatorio(0, armas.size() - 1);
    return Arma(armas[indice], potencia);
}

void Aleatorio::obtener_arma_aleatoria(Inventario<Arma, comp> &inventario_armas) {
    if(armas.empty()){
        cout << "No hay armas disponibles para obtener" << endl;
        return;
    }

    size_t indice = generar_numero_aleatorio(0, VECTOR_BOOLEANO.size() - 1);

    if(VECTOR_BOOLEANO[indice] == SUERTE) {
        inventario_armas.alta(generar_arma_aleatoria());
        cout << "Haz obtenido una nueva arma!" << endl;
    } else {
        cout << "Pucha :C no hay arma nueva, PIPIPI" << endl;
    }
}

Aleatorio::~Aleatorio() = default;

bool comp(Arma arma_1, Arma arma_2) {
    return arma_1 > arma_2;
}