#include "Grafo.h"

Grafo::Grafo(int nVertices)
{
    this->n = nVertices;
    this->a = 0;

    this->adjList.resize(n);
    this->colors.assign(n,-1);
}
void Grafo::addAresta(int u, int v)
{
    if( u < 0|| u >= n || v < 0 || v >= n)
    {
        cout << "Erro!" << endl;
        return;
    }

    this->adjList[u].push_back(v);
    this->adjList[v].push_back(u);
    this->a++;
}
int Grafo::getNumVertices()
{
    return this->n;
}
int Grafo::getNumArestas()
{
    return this->a;
}
const vector<int>& Grafo::getVizinhos(int u)
{
    if( u < 0 || u >= n)
    {
        static vector<int> vazia;
        return vazia;
    }

    return this->adjList[u];

}
int Grafo::getGrau(int u)
{
    if(u >= 0 && u < n){
        return this->adjList[u].size();
    }
    return -1;
}

int Grafo::getColor(int v)
{
    return this->colors[v];
}

void Grafo::setColor(int v, int color)
{
    if(v >= 0 && v < n){
        this->colors[v] = color;
    }
}