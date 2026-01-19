#include "Algoritimos.h"

Algoritimos::Algoritimos(Grafo* g)
{
    this->grafo = g;
}

Algoritimos::~Algoritimos()
{
}

vector<int> Algoritimos::guloso(unsigned semente)
{
    int n = grafo->getNumVertices();
    const auto& adjList = grafo->getAdjList();
    
    vector<int> ordemVertices(n);
    for(int i = 0; i < n; ++i) {
        ordemVertices[i] = i;
    }
    sort(ordemVertices.begin(), ordemVertices.end(), [&](int a, int b) {
        return adjList[a].size() > adjList[b].size();
    });

    vector<int> cores(n, -1);
    for (int u : ordemVertices) {
        cores[u] = grafo->obterMenorCorValida(u, cores);
    }
    
    return cores;
}

vector<int> Algoritimos::gulosoRandomizado(unsigned semente)
{
    int n = grafo->getNumVertices();
    
    vector<int> ordemVertices(n);
    for(int i = 0; i < n; ++i) {
        ordemVertices[i] = i;
    }
    mt19937 gerador(semente);
    shuffle(ordemVertices.begin(), ordemVertices.end(), gerador);

    vector<int> cores(n, -1);
    for (int u : ordemVertices) {
        cores[u] = grafo->obterMenorCorValida(u, cores);
    }
    
    return cores;
}

vector<int> Algoritimos::gulosoReativo(int iteracoes)
{
    int n = grafo->getNumVertices();
    
    vector<int> melhoresCores;
    int menorMaiorCor = 1e9;
    unsigned sementeBase = chrono::system_clock::now().time_since_epoch().count();
    
    for (int i = 0; i < iteracoes; ++i) {
        vector<int> ordemVertices(n);
        for(int j = 0; j < n; ++j) {
            ordemVertices[j] = j;
        }

        mt19937 gerador(sementeBase + i);
        shuffle(ordemVertices.begin(), ordemVertices.end(), gerador);

        vector<int> coresAtuais(n, -1);
        for (int u : ordemVertices) {
            coresAtuais[u] = grafo->obterMenorCorValida(u, coresAtuais);
        }
        int maiorCorNessaTentativa = -1;
        for(int c : coresAtuais) {
            if(c > maiorCorNessaTentativa) maiorCorNessaTentativa = c;
        }
        if (maiorCorNessaTentativa < menorMaiorCor) {
            menorMaiorCor = maiorCorNessaTentativa;
            melhoresCores = coresAtuais;
        }
    }
    
    return melhoresCores;
}
