#ifndef SOLVER_H
#define SOLVER_H

#include "Grafo.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cmath>

class Solver {
private:
    
    static bool isSafe(Grafo* g, int u, int c, int d);

    
    struct VertexDegree {
        int id;
        int degree;
    };
    
    
    static bool compareDegree(const VertexDegree& a, const VertexDegree& b) {
        return a.degree > b.degree;
    }

public:
    
    static int greedyColoring(Grafo* g, int d);

    
    static int randomizedGreedyConstruction(Grafo* g, int d, float alpha);

   
    static int solveRandomized(Grafo* g, int d, float alpha, int numIterations);

 
    static int solveReactive(Grafo* g, int d, int numIterations, int blockSize, std::vector<float>& alphas);
};

#endif