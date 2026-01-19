#include <iostream>
#include "Grafo.h"
#include "Utils.h"


using  namespace  std;

int main() {

    string filePath;
    Grafo* g = Utils::readAndCreate(filePath = "../dsjc250.5.txt");


    for(int i = 0; i < 250; i++)
        cout << g->getGrau(i) << endl;

    cout << "Numero de arestas = " << g->getNumArestas() << endl;
    Utils::saveAndExport(g,"../results.txt");
    Utils::saveAndExport(g,"../results_color.txt",1);
    


    return 0;
}