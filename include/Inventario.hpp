#ifndef ALGO2_TP3_PT2_Inventario_H
#define ALGO2_TP3_PT2_Inventario_H

#include "Heap.hpp"
#include "Arma.hpp"

template<typename T,bool comp(T,T)>

class Inventario{
private:
    Heap<T,comp>* heapMaxima;

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
};

template<typename T,bool comp(T,T)>
Inventario<T,comp>::Inventario(){
    this-> heapMaxima = new Heap<T, comp>();
}


template<typename T,bool comp(T,T)>
void Inventario<T,comp>::alta(T dato){
    heapMaxima->alta(dato);
}

template<typename T,bool comp(T,T)>
T Inventario<T, comp>::consulta() {
    return heapMaxima -> primero();
}

template<typename T,bool comp(T,T)>
T Inventario<T, comp>::baja() {
    return heapMaxima -> baja();
}

#endif
