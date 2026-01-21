#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <numeric>
#include <ctime>
#include <sstream>

#include "Grafo.h"
#include "Utils.h"
#include "Solver.h"

using namespace std;

const int NUM_EXECUCOES = 10;
const int D_DEFECT = 2;

const int ITER_RANDOM = 30;
const int ITER_REACTIVE = 300;
const int BLOCO_REACTIVE = 50;

struct Resultados {
    string nomeAlgoritmo;
    int melhorSolucao;
    double mediaSolucoes;
    double tempoMedio;
};

template <typename Func>
Resultados rodarBateria(string nomeAlgoritmo, Func algoritmo) {
    long somaSolucoes = 0;
    double somaTempos = 0;
    int melhorGeral = 2147483647;

    unsigned int seedBase = time(NULL);

    cout << "   > " << nomeAlgoritmo << "... ";
    
    for (int i = 0; i < NUM_EXECUCOES; i++) {
        unsigned int seed = seedBase + (i * 777);
        srand(seed);

        auto start = chrono::high_resolution_clock::now();
        
        int solucao = algoritmo(); 

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;

        somaSolucoes += solucao;
        somaTempos += diff.count();
        if (solucao < melhorGeral) melhorGeral = solucao;
    }
    
    cout << "Concluido. (Melhor: " << melhorGeral << ")" << endl;

    Resultados res;
    res.nomeAlgoritmo = nomeAlgoritmo;
    res.melhorSolucao = melhorGeral;
    res.mediaSolucoes = (double)somaSolucoes / NUM_EXECUCOES;
    res.tempoMedio = somaTempos / NUM_EXECUCOES;

    return res;
}

void processarInstancia(string filename) {
    cout << "========================================" << endl;
    cout << "PROCESSANDO: " << filename << endl;
    cout << "========================================" << endl;

    Grafo* g = Utils::readAndCreate("../instances/" + filename); 
    
    if (!g) {
        cerr << "Erro ao abrir arquivo de entrada: " << filename << endl;
        return;
    }

    vector<Resultados> tabela;

    tabela.push_back(rodarBateria("Guloso", [&]() {
        return Solver::greedyColoring(g, D_DEFECT);
    }));

    vector<float> alphasTeste = {0.2f, 0.3f, 0.4f};
    
    for(float alpha : alphasTeste) {
        stringstream ss;
        ss << "Randomizado (a=" << fixed << setprecision(1) << alpha << ")";
        string nomeAlgo = ss.str();

        tabela.push_back(rodarBateria(nomeAlgo, [&, alpha]() {
            return Solver::solveRandomized(g, D_DEFECT, alpha, ITER_RANDOM);
        }));
    }

    vector<float> poolReativo = {0.2f, 0.3f, 0.4f};
    tabela.push_back(rodarBateria("Reativo (Pool 0.2-0.4)", [&]() {
        return Solver::solveReactive(g, D_DEFECT, ITER_REACTIVE, BLOCO_REACTIVE, poolReativo);
    }));

    string outputName = "results/resultados_" + filename + ".csv";
    ofstream csvFile(outputName);

    if (!csvFile.is_open()) {
        cerr << "ERRO: Nao foi possivel criar o arquivo " << outputName << endl;
    } else {
        csvFile << "Instancia;Algoritmo;Melhor_Sol;Media_Sol;Tempo_Medio(s)" << endl;

        for (const auto& r : tabela) {
            csvFile << filename << ";"
                    << r.nomeAlgoritmo << ";"
                    << r.melhorSolucao << ";"
                    << fixed << setprecision(2) << r.mediaSolucoes << ";"
                    << fixed << setprecision(4) << r.tempoMedio << endl;
        }

        csvFile.close();
        cout << ">> CSV salvo com sucesso: " << outputName << endl << endl;
    }

    delete g;
}

int main() {
    
    vector<string> instancias = {
        "C2000.5.col.txt",
        "C4000.5.col.txt",
        "dsjc250.5.txt",
        "dsjc500.1.col.txt",
        "dsjc500.5.col.txt",
        "dsjc500.9.col.txt",
        "dsjc1000.1.col.txt",
        "dsjc1000.5.col.txt",
        "dsjc1000.9.col.txt",
        "dsjr500.1c.col.txt",
        "dsjr500.5.col.txt",
        "flat300_28_0.col.txt",
        "flat1000_50_0.col.txt",
        "flat1000_60_0.col.txt",
        "flat1000_76_0.col.txt",
        "latin_square.col.txt",
        "le450_25c.col.txt",
        "le450_25d.col.txt",
        "r250.5.col.txt",
        "r1000.1c.col.txt",
        "r1000.5.col.txt"
    };

    cout << "--- BATERIA DE TESTES (OUTPUT NA RAIZ) ---" << endl;
    cout << "Parametros: d=" << D_DEFECT 
         << " | Execs=" << NUM_EXECUCOES << endl;

    for (const string& arquivo : instancias) {
        processarInstancia(arquivo);
    }

    cout << "--- FIM ---" << endl;
    return 0;
}