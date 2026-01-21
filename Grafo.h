#ifndef TRABALHO_DCC059_GRAFO_H
#define TRABALHO_DCC059_GRAFO_H
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Grafo {


private:
    int n;
    int a;
    vector<vector<int>> adjList;
    vector<int> colors;

    
 


public:
    Grafo(int nVertices);
    void addAresta(int u, int v);
    int getNumVertices();
    int getNumArestas();
    const vector<int>& getVizinhos(int u);
    int getGrau(int u);
    int getColor(int v);
    string getAresta(int u, int v);
    void resetColors();
    void setColor(int v, int cor);
    int countDefects(int v);
    


};

enum Colors {
    VERMELHO,
    AZUL,
    AMARELO,
    ROSA,
    VERDE,
    CIANO,
    LARANJA,
    BRANCO,
    PRETO,
    ROXO
};

#endif