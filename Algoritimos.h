#ifndef TRABALHO_DCC059_ALGORITIMOS_H
#define TRABALHO_DCC059_ALGORITIMOS_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Grafo.h"

using namespace std;

class Algoritimos {

private:
    Grafo* grafo;  // Ponteiro para o grafo a ser colorido

public:
    Algoritimos(Grafo* g);
    ~Algoritimos();

    // Algoritmo Guloso (Determinístico - Ordenado por Grau)
    vector<int> guloso(unsigned semente = 0);

    // Algoritmo Guloso Randomizado
    vector<int> gulosoRandomizado(unsigned semente = 42);

    // Algoritmo Guloso Randomizado Reativo (Iterativo)
    vector<int> gulosoReativo(int iteracoes = 100);
};

#endif //TRABALHO_DCC059_ALGORITIMOS_H
