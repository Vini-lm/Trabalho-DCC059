#include "Utils.h"


Utils::Utils()
{

}

Utils::~Utils()
{
}



Grafo *Utils::readAndCreate(string filePath)
{
    ifstream inFile;

    inFile.open(filePath, ios::in);

    if (!inFile)
    {
        cout << "Erro, Arquivo não encontrado" << endl;
        return nullptr;
    }

    string l, trash;
    int numVertices, numArestas, u, v;
    numVertices = numArestas = u = v = 0;
    Grafo *grafo = nullptr;

    while (getline(inFile, l))
        
    {
        if (l[0] == 'p')
        {
            stringstream ss(l);
            ss >> trash;
            ss >> trash;
            ss >> numVertices;
            ss >> numArestas;
            break;
        }
    }

    grafo = new Grafo(numVertices);
    cout << "Grafo criado com " << numVertices << " Vertices." << endl;

    while (getline(inFile, l))
    {
        if(l[0] == 'e'){
            stringstream ss(l);
            ss >> trash;
            ss >> u;
            ss >> v;
            grafo->addAresta(u - 1, v - 1);
        }
    }
    inFile.close();

    return grafo;
}