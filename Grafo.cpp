#include "Grafo.h"

Grafo::Grafo(int nVertices)
{
    this->n = nVertices;
    this->a = 0;
    this->paramP = 1;
    this->paramQ = 0;
    this->adjList.resize(n);
    this->colors.assign(n,-1);
}

Grafo::Grafo(int nVertices, int p, int q)
{
    this->n = nVertices;
    this->a = 0;
    this->paramP = p;
    this->paramQ = q;
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

void Grafo::adicionarAresta(int u, int v)
{
    addAresta(u, v);
}

int Grafo::getNumVertices() const
{
    return this->n;
}

int Grafo::getNumArestas()
{
    return this->a;
}

const vector<int>& Grafo::getVizinhos()
{
    static vector<int> empty;
    return empty;
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
    if(v >= 0 && v < n) {
        this->colors[v] = color;
    }
}

const vector<vector<int>>& Grafo::getAdjList() const
{
    return this->adjList;
}

bool Grafo::corEhSegura(int u, int corTentativa, const vector<int>& coresAtuais)
{
    for (int vizinho : adjList[u]) {
        if (coresAtuais[vizinho] != -1) {
            if (abs(corTentativa - coresAtuais[vizinho]) < paramP) return false;
        }
        
        for (int vizinhoDoVizinho : adjList[vizinho]) {
            if (vizinhoDoVizinho != u && coresAtuais[vizinhoDoVizinho] != -1) {
                if (abs(corTentativa - coresAtuais[vizinhoDoVizinho]) < paramQ) return false;
            }
        }
    }
    return true;
}

int Grafo::obterMenorCorValida(int u, const vector<int>& cores)
{
    int cor = 0;
    while (!corEhSegura(u, cor, cores)) {
        cor++;
    }
    return cor;
}

void Grafo::imprimirSolucaoDOT(const vector<int>& cores, string titulo)
{
    cout << "// " << titulo << "\n";
    cout << "graph G {\n";
    cout << "  node [style=filled, fontname=\"Arial\"];\n";
    for (int i = 0; i < n; ++i) {
        cout << "  " << i << " [label=\"" << i << "\\n(Cor " << cores[i] << ")\"";
        cout << ", fillcolor=\"/set312/" << (cores[i] % 12 + 1) << "\"];\n";
    }
    for (int u = 0; u < n; ++u) {
        for (int v : adjList[u]) {
            if (u < v) {
                cout << "  " << u << " -- " << v << ";\n";
            }
        }
    }
    cout << "}\n\n";
}