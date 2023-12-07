#include <iostream>
#include "ABBv2.hpp"
#include "Placa.hpp"
#include "bGVjdG9y/bGVjdG9y.hpp"
#include "bGVjdG9y/ZGVjb2Rl.hpp"

using namespace std;

int main()
{
    ABB<Placa*, Placa::menor, Placa::igual> ABB_placas;
    bGVjdG9y::Y2FyZ2Fy(ABB_placas);

    std::vector<Placa *> placas = ABB_placas.preorder();

    for (Placa* placa: placas){
        std::cout << *placa;
    }

    return 0;
}
