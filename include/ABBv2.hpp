#ifndef ABB_H
#define ABB_H

#include <exception>
#include "NodoABBv2.hpp"
#include <iostream>

class ABB_exception : public std::exception {
};

template<typename T, bool menor(T, T), bool igual(T, T)>
class ABB {
private:
    NodoABB<T, menor, igual>* raiz;
    std::size_t cantidad_datos;

    // Pre: -
    // Post: Agrega el dato al árbol.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void alta(T dato, NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Elimina el dato del árbol y devuelve la nueva raiz, de haberla.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void baja(T dato, NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Devuelve true si el dato está en el subárbol.
    bool consulta(T dato, NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido inorder.
    void inorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido preorder.
    void preorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido postorder.
    void postorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos);

    // Pre: -
    // Post: Ejecuta el método/función en el subárbol.
    void ejecutar(void metodo(T), NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Inicializa los atributos del nodo.       
    void inicializar_nodo(NodoABB<T, menor, igual>* nodo, T dato, NodoABB<T, menor, igual>* padre);

    // Pre: -
    // Post: Libera la memoria de los nodos.       
    void liberar_memoria(NodoABB<T, menor, igual>* nodo_actual);


public:
    // Constructor.
    ABB();

    // Pre: El dato a ingresar no puede estar en el árbol.
    // Post: Agrega el dato al árbol. Si no hay datos, crea una nueva raiz.
    void alta(T dato);

    // Pre: -
    // Post: Elimina el dato del árbol. Si no existe, no hace nada.
    // NOTA: Si la raiz cambia (sin importar el caso), se debe reasignar correctamente.
    void baja(T dato);

    // Pre: -
    // Post: Devuelve true si el dato está en el árbol. Si no hay datos, devuelve false.
    bool consulta(T dato);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    std::vector<T> inorder();

    // Pre: -
    // Post: Devuelve el recorrido preorder.
    std::vector<T> preorder();

    // Pre: -
    // Post: Devuelve el recorrido postorder.
    std::vector<T> postorder();

    // Pre: -
    // Post: Devuelve el recorrido en ancho.
    std::vector<T> ancho();

    // Pre: -
    // Post: Ejecuta el método/función en cada uno de los nodos.
    // NOTA: No abusar de este método, está solamente para simplificar
    // algunas cosas, como liberar la memoria de los nodos de usar punteros
    // o imprimir por pantalla el contenido. Pueden usar cualquier recorrido.
    void ejecutar(void metodo(T));

    // Pre: -
    // Post: Devuelve la cantidad de datos en el árbol.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el árbol está vacio.
    bool vacio();

    // El constructor de copia está deshabilitado.
    ABB(const ABB& abb) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const ABB& abb) = delete;

    // Destructor.
    ~ABB();
};

template<typename T, bool menor(T, T), bool igual(T, T)>
ABB<T, menor, igual>::ABB() {
    raiz = nullptr;
    cantidad_datos = 0;
}

template<typename T, bool menor(T, T), bool igual(T, T)>        
void ABB<T, menor, igual>::inicializar_nodo(NodoABB<T, menor, igual>* nodo, T dato, NodoABB<T, menor, igual>* padre) {
    nodo -> dato = dato;
    nodo -> padre = padre;
    nodo -> hijo_izquierdo = nullptr;
    nodo -> hijo_derecho = nullptr;
}

template<typename T, bool menor(T, T), bool igual(T, T)>         
void ABB<T, menor, igual>::alta(T dato) {
    if (vacio()) {
        raiz = new NodoABB<T, menor, igual>;
        inicializar_nodo(raiz, dato, nullptr);
        cantidad_datos ++;
    } else if (igual(dato, raiz -> dato)) {
        throw ABB_exception();
    } else if (menor(dato, raiz -> dato)) {
        if (raiz -> hijo_izquierdo == nullptr) {
            raiz -> hijo_izquierdo = new NodoABB<T, menor, igual>;
            inicializar_nodo(raiz -> hijo_izquierdo, dato, raiz);
            cantidad_datos ++;
        } else {
            alta(dato, raiz -> hijo_izquierdo);
        }
    } else {
        if (raiz -> hijo_derecho == nullptr) {
            raiz -> hijo_derecho = new NodoABB<T, menor, igual>;
            inicializar_nodo(raiz -> hijo_derecho, dato, raiz);
            cantidad_datos ++;
        } else {
            alta(dato, raiz -> hijo_derecho);
        }
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>             
void ABB<T, menor, igual>::alta(T dato, NodoABB<T, menor, igual>* nodo_actual) {
    if (igual(dato, nodo_actual -> dato)) {
        throw ABB_exception();
    } else if (menor(dato, nodo_actual -> dato)) {
        if (nodo_actual -> hijo_izquierdo == nullptr) {
            nodo_actual -> hijo_izquierdo = new NodoABB<T, menor, igual>;
            inicializar_nodo(nodo_actual -> hijo_izquierdo, dato, nodo_actual);
            cantidad_datos ++;
        } else {
            alta(dato, nodo_actual -> hijo_izquierdo); 
        }
    } else {
        if (nodo_actual -> hijo_derecho == nullptr) {
            nodo_actual -> hijo_derecho = new NodoABB<T, menor, igual>;
            inicializar_nodo(nodo_actual -> hijo_derecho, dato, nodo_actual);
            cantidad_datos ++;
        } else {
            alta(dato, nodo_actual -> hijo_derecho); 
        }
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>    
void ABB<T, menor, igual>::liberar_memoria(NodoABB<T, menor, igual>* nodo_actual) {
    if (nodo_actual -> hijo_izquierdo != nullptr) {
        liberar_memoria(nodo_actual -> hijo_izquierdo);
    }
    if (nodo_actual -> hijo_derecho != nullptr) {
        liberar_memoria(nodo_actual -> hijo_derecho);
    }
    delete nodo_actual;
}

template<typename T, bool menor(T, T), bool igual(T, T)>       
ABB<T, menor, igual>::~ABB() {
    liberar_memoria(raiz);
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T, menor, igual>::vacio(){
    return (cantidad_datos==0);
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::size_t ABB<T,menor,igual>::tamanio(){
    return cantidad_datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T,menor,igual>::consulta(T dato){ /*Metodo Publico*/
    bool encontrado=false;
    if(raiz == nullptr){
        encontrado = false;
    }else{
        if(igual(dato,raiz->dato)){
            encontrado = true;
        }else{
            if(menor(dato,raiz->dato)){
                encontrado = consulta(dato,raiz->hijo_izquierdo);
            }else{
                encontrado = consulta(dato,raiz->hijo_derecho);
            }
        }
    }
    return encontrado;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T,menor,igual>::consulta(T dato, NodoABB<T, menor, igual>* nodo_actual){ /*Metodo Privado*/
    bool encontrado = false;
    if(nodo_actual == nullptr){
        encontrado = false;
    }else{
        if(igual(dato,nodo_actual->dato)){
            encontrado = true;
        }else{
            if(menor(dato,nodo_actual->dato)){
                encontrado = consulta(dato,nodo_actual->hijo_izquierdo);
            }else{
                encontrado = consulta(dato,nodo_actual->hijo_derecho);
            }
        }
    }
    return encontrado;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T,menor,igual>::ancho(){
    std::queue<NodoABB<T,menor,igual>> cola;
    std::vector<T> vect;

    if(raiz==nullptr){
        throw ABB_exception();
    }else{
        cola.push(*raiz);
        while(!cola.empty()){
            NodoABB<T,menor,igual> actual = cola.front();
            cola.pop();
            vect.push_back(actual.dato);
            if(actual.hijo_izquierdo!=nullptr){
                cola.push(*actual.hijo_izquierdo);
            }
            if(actual.hijo_derecho!=nullptr){
                cola.push(*actual.hijo_derecho);
            }
        }
    }
    return vect;
}

template<typename T, bool menor(T, T), bool igual(T, T)>            // SUBIR EN EL TERCER COMMIT
std::vector<T> ABB<T, menor, igual>::inorder() {
    std::vector<T> elementos;
    if (!vacio()) {
        inorder(raiz, elementos);
    }
    return elementos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>             // SUBIR EN EL TERCER COMMIT
void ABB<T, menor, igual>::inorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos) {
    if (nodo_actual -> hijo_izquierdo != nullptr) {
        inorder(nodo_actual -> hijo_izquierdo, datos);  
    }
    datos.push_back(nodo_actual -> dato);
    if (nodo_actual -> hijo_derecho != nullptr) {
        inorder(nodo_actual -> hijo_derecho, datos); 
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T, menor, igual>::preorder(){
    std::vector<T> datos;
    preorder(raiz, datos);
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::preorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos){
    if (nodo_actual != nullptr) {
        datos.push_back(nodo_actual -> dato);
        preorder(nodo_actual -> hijo_izquierdo, datos);
        preorder(nodo_actual -> hijo_derecho, datos);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T>  ABB<T, menor, igual>::postorder() {
    std::vector<T> datos;
    postorder(raiz, datos);
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::postorder(NodoABB<T, menor, igual> *nodo_actual, std::vector<T> &datos) {
    if (nodo_actual != nullptr) {
        postorder(nodo_actual -> hijo_izquierdo, datos);
        postorder(nodo_actual -> hijo_derecho, datos);
        datos.push_back(nodo_actual -> dato);
    }
}

#endif
