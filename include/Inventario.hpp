#ifndef ALGO2_TP3_PT2_Inventario_H
#define ALGO2_TP3_PT2_Inventario_H

#include "Heap.hpp"
#include "Arma.hpp"
const size_t MAX_CAPACIDAD = 15;
template<typename T,bool comp(T,T)>

class Inventario{
private:
    Heap<T,comp>* heapMaxima;
    size_t cantidad_datos;
public:
    //Constructor
    Inventario();

    //Pre: Ingresa un dato.
    //Post: Ingresa el dato al heap.
    void alta(T dato);

    //Pre: El inventario no debe estar vacio.
    //Post: Quita y Devuelve el arma de mayor prioridad.
    T baja();

    //Pre: El inventario no debe estar vacio.
    //Post: Devuelve el arma de mayor prioridad.
    T consulta();

    //Pre:
    //Post: Duvuelve true si el inventario se encuentra lleno.
    bool esta_lleno();

    //Pre:-
    //Post: Devuelve true si el inventario se encuentra vacio.
    bool vacio();

    //Pre:-
    //Post:Devuelve la cantidad de datos.
    size_t tamanio();

    // Destructor
    ~Inventario();
    
};

template<typename T,bool comp(T,T)>
Inventario<T,comp>::Inventario(){
    this-> heapMaxima = new Heap<T, comp>();
    this->cantidad_datos=0;
}


template<typename T,bool comp(T,T)>
void Inventario<T,comp>::alta(T dato){
    if(!esta_lleno()){
        heapMaxima->alta(dato);
        cantidad_datos++;
    }
}

template<typename T,bool comp(T,T)>
T Inventario<T, comp>::consulta() {
    return heapMaxima -> primero();
}

template<typename T,bool comp(T,T)>
T Inventario<T, comp>::baja() {
    cantidad_datos--;
    return heapMaxima -> baja();
}

template<typename T,bool comp(T,T)>
size_t Inventario<T,comp>::tamanio(){
    return cantidad_datos;
}

//begin

template<typename T,bool comp(T,T)>
bool Inventario<T,comp>::esta_lleno(){
    return cantidad_datos == MAX_CAPACIDAD;
}

template<typename T,bool comp(T,T)>
bool Inventario<T,comp>::vacio(){
    return cantidad_datos == 0;
}

template<typename T,bool comp(T,T)>
Inventario<T,comp>::~Inventario() {
    delete heapMaxima;
}

#endif
