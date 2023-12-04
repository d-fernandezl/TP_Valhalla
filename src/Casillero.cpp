#include "Casillero.hpp"

Casillero::Casillero(int numero,std::string objeto){
    this->numero = numero;
    this->objeto = objeto;
}
std::string Casillero::obtener_objeto(){
    return objeto;
}
int Casillero::obtener_numero(){
    return numero;
}