#include "Juego.hpp"

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
Juego<comp,menor,igual>::Juego(){
    rondas = 1;
    tablero = Tablero();
    player = Jugador<comp,menor,igual>(0,true);
}

template<bool comp(Arma,Arma),bool menor(Placa,Placa),bool igual(Placa,Placa)>
void Juego<comp,menor,igual>::iniciar_juego(){
    while(rondas<=RONDAS_MAXIMAS){ // Faltaria agregar que mientras sea posible llegar a la salida
        //Verifica la altura del arbol de placas arbol de placas.
        size_t altura = player.altura_del_arbol();
        //Crea las paredes del tablero segun la altura del arbol.
        if(altura%2==0){
            std::vector<int> layout1 {
            3,12,21,39,48,57,75,10,19,28,37,55,64,73,
            14,23,32,50,59,68,77,16,25,34,43,52,70,79
            };
            tablero.asignar_paredes(layout1);
        }else{
            std::vector<int> layout2 {
            3,10,12,14,16,17,23,28,29,30,32,34,43,45,46,48,49,50,61,64,65,66,67,68,70
            };
            tablero.asignar_paredes(layout2);
        }
        
        bool finalizado=false;
        while(!finalizado){
            //Menu de opciones
            if(player.obtener_posicion()==COTA_SUPERIOR){
                if(rondas<RONDAS_MAXIMAS){
                    std::cout<<"Felicidades pasastes de nivel.";
                    //Si llega al final termina el nivel se le avisa al jugador y se le da una placa
                    //Entregar Placa y arma
                }else{
                    std::cout<<"Felicidades pasastes el juego.";
                }
                finalizado=true;
            }
        }

        //se aumenta 1 a las rondas y vuelve al inicio
        rondas++;
    }
}
