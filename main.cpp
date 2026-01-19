#include "Grafo.h"
#include "Utils.h"
#include "Algoritimos.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool validarColorcao(const Grafo* g, const vector<int>& cores) {
    const auto& adjList = g->getAdjList();
    int n = g->getNumVertices();
    
    for (int u = 0; u < n; ++u) {
        for (int v : adjList[u]) {
            if (cores[u] == cores[v]) {
                return false;
            }
        }
    }
    return true;
}

int contarCoresUsadas(const vector<int>& cores) {
    int maxCor = 0;
    for (int c : cores) {
        maxCor = max(maxCor, c);
    }
    return maxCor + 1;
}

void executarTeste(const string& nomeTeste, bool resultado) {
    cout << "[" << (resultado ? "PASS" : "FAIL") << "] " << nomeTeste << endl;
}

void testarAlgoritmo(const Grafo* g, const vector<int>& resultado, const string& nomeAlgoritmo) {
    bool valido = validarColorcao(g, resultado);
    int numCores = contarCoresUsadas(resultado);
    
    executarTeste(nomeAlgoritmo + " - Coloração válida", valido);
    cout << "        Cores usadas: " << numCores << endl;
}

int main() {
    int p = 2, q = 1;

    int numNos = 6;
    Grafo meuGrafo(numNos, p, q);
    meuGrafo.addAresta(0, 2);
    meuGrafo.addAresta(0, 4);
    meuGrafo.addAresta(0, 5);
    meuGrafo.addAresta(1, 4);
    meuGrafo.addAresta(1, 5);
    meuGrafo.addAresta(2, 3);
    meuGrafo.addAresta(2, 4);
    meuGrafo.addAresta(4, 5);
    Algoritimos algo(&meuGrafo);
    
    cout << "\n=== TESTES DOS ALGORITMOS DE COLORAÇÃO ===" << endl;
    cout << "Parâmetros: L(" << p << "," << q << ")" << endl;
    cout << "Vertices: " << meuGrafo.getNumVertices() << endl;
    cout << "Arestas: " << meuGrafo.getNumArestas() << endl;
    cout << "\n--- Executando testes ---\n" << endl;
    
    vector<int> guloso_result = algo.guloso();
    testarAlgoritmo(&meuGrafo, guloso_result, "Guloso");
    
    vector<int> randomizado_result = algo.gulosoRandomizado(42);
    testarAlgoritmo(&meuGrafo, randomizado_result, "Guloso Randomizado");
    
    int iteracoes = 100;
    vector<int> reativo_result = algo.gulosoReativo(iteracoes);
    testarAlgoritmo(&meuGrafo, reativo_result, "Guloso Reativo (" + to_string(iteracoes) + " iterações)");
    
    int max_guloso = contarCoresUsadas(guloso_result);
    int max_randomizado = contarCoresUsadas(randomizado_result);
    int max_reativo = contarCoresUsadas(reativo_result);
    
    cout << "\n--- Validação geral ---\n" << endl;
    executarTeste("Todas as colorações são válidas", 
                  validarColorcao(&meuGrafo, guloso_result) && 
                  validarColorcao(&meuGrafo, randomizado_result) && 
                  validarColorcao(&meuGrafo, reativo_result));
    
    cout << "\n=== RESULTADOS COMPARATIVOS ===" << endl;
    cout << setw(30) << "Algoritmo" << setw(15) << "Cores Usadas" << endl;
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    cout << setw(30) << "Guloso" << setw(15) << max_guloso << endl;
    cout << setw(30) << "Guloso Randomizado" << setw(15) << max_randomizado << endl;
    cout << setw(30) << "Guloso Reativo (100 it.)" << setw(15) << max_reativo << endl;
    
    int melhor = min({max_guloso, max_randomizado, max_reativo});
    cout << "\n--- Conclusão ---\n" << endl;
    cout << "Melhor resultado: " << melhor << " cores" << endl;
    if (melhor == max_reativo) {
        cout << "Vencedor: Guloso Reativo" << endl;
    } else if (melhor == max_randomizado) {
        cout << "Vencedor: Guloso Randomizado" << endl;
    } else {
        cout << "Vencedor: Guloso (Determinístico)" << endl;
    }
    
    cout << "\n=== SOLUÇÃO GULOSO EM DOT ===" << endl;
    meuGrafo.imprimirSolucaoDOT(guloso_result, "Solucao Guloso");
    
    return 0;
}
