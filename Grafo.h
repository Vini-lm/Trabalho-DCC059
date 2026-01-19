#ifndef TRABALHO_DCC059_GRAFO_H
#define TRABALHO_DCC059_GRAFO_H
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

class Grafo {

private:
    int n;
    int a;
    vector<vector<int>> adjList;
    vector<int> colors;
    int paramP, paramQ;

public:
    Grafo(int nVertices);
    Grafo(int nVertices, int p, int q);
    void addAresta(int u, int v);
    void adicionarAresta(int u, int v);
    int getNumVertices() const;
    int getNumArestas();
    const vector<int>& getVizinhos(int u);
    int getGrau(int u);
    int getColor(int v);
    void setColor(int v, int cor);
    const vector<vector<int>>& getAdjList() const;
    bool corEhSegura(int u, int corTentativa, const vector<int>& coresAtuais);
    int obterMenorCorValida(int u, const vector<int>& cores);
    void imprimirSolucaoDOT(const vector<int>& cores, string titulo);
    string getAresta(int u, int v);
    


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

#endif //TRABALHO_DCC059_GRAFO_H