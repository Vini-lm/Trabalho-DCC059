#ifndef TRABALHO_DCC059_GRAFO_H
#define TRABALHO_DCC059_GRAFO_H
#include <vector>

using namespace std;

class Grafo {


private:
    int n;
    vector<vector<int>> adjList;
    vector<int> colors;
 


public:
    Grafo(int nVertices);
    void addAresta(int u, int v);

    int getNumVertices();
    int getNumArestas();
    vector<int>& getVizinhos();
    int getGrau(int u);

    
};


#endif //TRABALHO_DCC059_GRAFO_H