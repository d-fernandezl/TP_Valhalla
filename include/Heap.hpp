#ifndef ALGO2_TP3_PT2_HEAP_H
#define ALGO2_TP3_PT2_HEAP_H

#include <vector>
#include <cstdlib>
#include <exception>

class Heap_exception : public std::exception {
};

template<typename T, bool comp(T, T)>
class Heap {
private:
    std::vector<T> datos;

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Intercambia de lugar los datos de los indices indicados.
    void swap(size_t index_1, size_t index_2);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Realiza un "upheap" sobre los índices indicados.
    // (El dato "sube" en el heap.)
    void upheap(size_t& index, size_t& parent_index);

    // Post: El índice debe ser menor que la cantidad de datos.
    // Post: Realiza un "downheap" sobre el índice indicado.
    // (El dato "baja" en el heap, intercambiándose con el menor/mayor dato.)
    void downheap(size_t& index_movido);

    void restauracion_descendente(size_t posicion_actual);

    // NOTA: No es necesario que lancen excepciones en estos métodos porque son privados.
    // Deberian siempre asegurar que los indices pasados por parámetros son válidos.
    // Consideren cada caso con detenimiento.
    // Adicionalmente, tengan cuidado con el casteo de las variables, porque son size_t.
    // Hacer, por ejemplo, size_t i = 0; i - 1; produce un underflow.
public:
    // Constructor.
    Heap();

    // Pre: -
    // Post: Agrega el dato al Heap.
    void alta(T dato);

    // Pre: El heap no puede estar vacío.
    // Post: Elimina y devuelve el primer dato.
    T baja();

    // Pre: El heap no puede estar vacío.
    // Post: Devuelve el primer dato.
    T primero();

    // Pre: -
    // Post: Devuelve true si el heap está vacío.
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el heap.
    size_t tamanio();

    // El constructor de copia está deshabilitado.
    Heap(const Heap& heap) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Heap& heap) = delete;

    // Destructor.
    ~Heap();

    std::vector<T> devolver_vector();

};

template<typename T, bool comp(T, T)>
Heap<T,comp>::Heap(){
    this->datos = std::vector<T>();
}

template<typename T,bool comp(T,T)>
void Heap<T,comp>::alta(T dato){
    if(tamanio()==0){
        datos.push_back(dato);
    }else{
        size_t posicion=tamanio();
        size_t padre_posicion = (posicion-1)/2;
        datos.push_back(dato);
        upheap(posicion,padre_posicion);
    }
}

template<typename T,bool comp(T,T)>
size_t Heap<T,comp>::tamanio(){
    return datos.size();
}

template<typename T,bool comp(T,T)>
T Heap<T,comp>::primero(){
    return datos[0];
}

template<typename T,bool comp(T,T)>
void Heap<T,comp>::swap(size_t index_1, size_t index_2){
    T aux = datos[index_1];
    datos[index_1] = datos[index_2];
    datos[index_2] = aux;
}

template<typename T,bool comp(T,T)>
bool Heap<T, comp>::vacio() {
    return datos.size() == 0;
}

template<typename T, bool comp(T, T)>
T Heap<T, comp>::baja() {
    if (vacio()) {
        throw Heap_exception();
    }
    swap(0, tamanio() - 1);
    restauracion_descendente(0);
    T dato = datos.back();        
    datos.pop_back();               
    return dato;     
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::restauracion_descendente(size_t posicion_actual) {
    size_t posicion_hijo_izquierdo = (2 * posicion_actual) + 1;
    size_t posicion_hijo_derecho = (2 * posicion_actual) + 2;
    if (posicion_hijo_izquierdo < datos.size() - 1) {
        if (datos[posicion_hijo_izquierdo] > datos[posicion_actual]) {
            swap(posicion_actual, posicion_hijo_izquierdo);
            restauracion_descendente(posicion_hijo_izquierdo);
        }
    }
    
    if (posicion_hijo_derecho < datos.size() - 1) {
        if (datos[posicion_hijo_derecho] > datos[posicion_actual]) {
            swap(posicion_actual, posicion_hijo_derecho);
            restauracion_descendente(posicion_hijo_derecho);
        }
    }
}

template<typename T, bool comp(T, T)>
Heap<T, comp>::~Heap(){}

#endif
