#include "Solver.h"
#include <iostream>
#include <set>

bool Solver::isSafe(Grafo* g, int u, int c, int d) {
    int countU = 0;
    const vector<int>& vizinhos = g->getVizinhos(u);
    
    for (int v : vizinhos) {
        int colorV = g->getColor(v);
        
        if (colorV == c) {
            countU++;
            if (countU > d) return false;

            int countV = 0;
            for (int neighborOfV : g->getVizinhos(v)) {
                if (g->getColor(neighborOfV) == c) {
                    countV++;
                }
            }
            if (countV >= d) return false;
        }
    }
    return true;
}

int Solver::greedyColoring(Grafo* g, int d) {
    g->resetColors();
    int n = g->getNumVertices();
    
    vector<VertexDegree> vertices(n);
    for(int i=0; i<n; i++) {
        vertices[i].id = i;
        vertices[i].degree = g->getGrau(i);
    }
    sort(vertices.begin(), vertices.end(), compareDegree);

    int maxColor = 0;

    for (int i = 0; i < n; i++) {
        int u = vertices[i].id;
        int color = 0;
        
        while (true) {
            if (isSafe(g, u, color, d)) {
                g->setColor(u, color);
                if (color > maxColor) maxColor = color;
                break;
            }
            color++;
        }
    }
    return maxColor + 1;
}

int Solver::randomizedGreedyConstruction(Grafo* g, int d, float alpha) {
    g->resetColors();
    int n = g->getNumVertices();
    
    vector<VertexDegree> candidates;
    for(int i=0; i<n; i++) {
        candidates.push_back({i, g->getGrau(i)});
    }

    int maxColor = 0;

    while (!candidates.empty()) {
        sort(candidates.begin(), candidates.end(), compareDegree);

        int minDegree = candidates.back().degree;
        int maxDegree = candidates.front().degree;
        
        int rclSize = max(1, (int)(candidates.size() * alpha));
        
        int randIndex = rand() % rclSize;
        int u = candidates[randIndex].id;

        candidates.erase(candidates.begin() + randIndex);


        int color = 0;
        while (true) {
            if (isSafe(g, u, color, d)) {
                g->setColor(u, color);
                if (color > maxColor) maxColor = color;
                break;
            }
            color++;
        }
    }
    return maxColor + 1;
}

int Solver::solveRandomized(Grafo* g, int d, float alpha, int numIterations) {
    int bestResult = INT_MAX;
    vector<int> bestColors(g->getNumVertices());

    for(int i = 0; i < numIterations; i++) {
        int result = randomizedGreedyConstruction(g, d, alpha);
        
        if (result < bestResult) {
            bestResult = result;
            for(int v=0; v<g->getNumVertices(); v++) {
                bestColors[v] = g->getColor(v);
            }
        }
    }


    for(int v=0; v<g->getNumVertices(); v++) {
        g->setColor(v, bestColors[v]);
    }
    
    return bestResult;
}

int Solver::solveReactive(Grafo* g, int d, int numIterations, int blockSize, std::vector<float>& alphas) {
    int nAlphas = alphas.size();
    vector<double> probabilities(nAlphas, 1.0 / nAlphas);
    vector<double> sumResults(nAlphas, 0.0);
    vector<int> counts(nAlphas, 0);
    
    int bestGlobalResult = INT_MAX;
    vector<int> bestColors(g->getNumVertices());


    auto chooseAlphaIndex = [&](const vector<double>& probs) -> int {
        double r = (double)rand() / RAND_MAX;
        double cumsum = 0.0;
        for(int i=0; i<probs.size(); i++) {
            cumsum += probs[i];
            if (r <= cumsum) return i;
        }
        return probs.size() - 1;
    };

    for (int iter = 1; iter <= numIterations; iter++) {
        int alphaIdx = chooseAlphaIndex(probabilities);
        float alpha = alphas[alphaIdx];

        int result = randomizedGreedyConstruction(g, d, alpha);

        sumResults[alphaIdx] += result;
        counts[alphaIdx]++;

        if (result < bestGlobalResult) {
            bestGlobalResult = result;
            for(int v=0; v<g->getNumVertices(); v++) bestColors[v] = g->getColor(v);
        }

        if (iter % blockSize == 0) {
            double sumScores = 0;
            vector<double> scores(nAlphas);
            
            for(int k=0; k<nAlphas; k++) {
                if(counts[k] > 0) {
                    double avg = sumResults[k] / counts[k];
                    scores[k] = pow((double)bestGlobalResult / avg, 4);
                } else {
                    scores[k] = 0.01;
                }
                sumScores += scores[k];
            }

            for(int k=0; k<nAlphas; k++) {
                probabilities[k] = scores[k] / sumScores;
            }
        }
    }

    for(int v=0; v<g->getNumVertices(); v++) {
        g->setColor(v, bestColors[v]);
    }

    return bestGlobalResult;
}