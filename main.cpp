#include <iostream>
#include "Grafo.h"
#include "Utils.h"


using  namespace  std;

int main() {

    
    Grafo* g = Utils::readAndCreate("C:/Users/vinic/CLionProjects/Trabalho-DCC059/dsjc250.5.txt");


    for(int i = 0; i < 250; i++)
        cout << g->getGrau(i) << endl;

    cout <<"Numero de arestas = " << g->getNumArestas() << endl;


    return 0;
}