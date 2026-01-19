#include <iostream>
#include "Grafo.h"
#include "Utils.h"


using  namespace  std;

int main() {

    string filePath;
    Grafo* g = Utils::readAndCreate(filePath = "" );


    for(int i = 0; i < 250; i++)
        cout << g->getGrau(i) << endl;

    cout << "Numero de arestas = " << g->getNumArestas() << endl;
    Utils::saveAndExport(g,"results.txt");
    


    return 0;
}