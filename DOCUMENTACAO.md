# Documentação Completa do Projeto - Trabalho DCC059

## Sumário
1. [Visão Geral do Projeto](#visão-geral-do-projeto)
2. [Arquitetura do Sistema](#arquitetura-do-sistema)
3. [Documentação dos Arquivos](#documentação-dos-arquivos)
   - [Grafo.h](#grafoh)
   - [Grafo.cpp](#grafocpp)
   - [Algoritimos.h](#algoritimosh)
   - [Algoritimos.cpp](#algoritimoscpp)
   - [Utils.h](#utilsh)
   - [Utils.cpp](#utilscpp)
   - [main.cpp](#maincpp)

---

## Visão Geral do Projeto

Este projeto implementa algoritmos de coloração de grafos com restrições L(p,q), onde:
- **p**: distância mínima de cores entre vértices adjacentes
- **q**: distância mínima de cores entre vértices a distância 2

O sistema implementa três variações de algoritmos gulosos:
1. **Guloso Determinístico**: Ordena vértices por grau decrescente
2. **Guloso Randomizado**: Ordena vértices aleatoriamente
3. **Guloso Reativo**: Executa múltiplas iterações randomizadas e escolhe o melhor resultado

---

## Arquitetura do Sistema

```
┌─────────────┐
│   main.cpp  │  ← Ponto de entrada, testes e validação
└──────┬──────┘
       │
       ├─────────────────────────────────────┐
       │                                     │
       ▼                                     ▼
┌──────────────┐                    ┌──────────────┐
│ Algoritimos  │                    │    Utils     │
│   .h/.cpp    │                    │   .h/.cpp    │
└──────┬───────┘                    └──────┬───────┘
       │                                   │
       └──────────────┬────────────────────┘
                      ▼
              ┌──────────────┐
              │    Grafo     │
              │   .h/.cpp    │
              └──────────────┘
```

---

## Documentação dos Arquivos

---

### Grafo.h

Este arquivo define a classe `Grafo` e os tipos necessários para representação de grafos.

```cpp
#ifndef TRABALHO_DCC059_GRAFO_H
#define TRABALHO_DCC059_GRAFO_H
```
**Linhas 1-2**: Guards de inclusão para evitar múltiplas inclusões do mesmo arquivo header.

```cpp
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
```
**Linhas 3-9**: Inclusão de bibliotecas padrão do C++:
- `vector`: Para uso de arrays dinâmicos
- `iostream`: Para entrada/saída de dados
- `sstream`: Para manipulação de strings
- `algorithm`: Para algoritmos como sort
- `cmath`: Para funções matemáticas (abs)
- `random`: Para geração de números aleatórios
- `chrono`: Para medição de tempo

```cpp
using namespace std;
```
**Linha 11**: Declaração do namespace padrão para evitar uso de `std::` antes de cada elemento.

```cpp
class Grafo {
```
**Linha 13**: Declaração da classe `Grafo`, que representa um grafo não-direcionado.

```cpp
private:
    int n;
    int a;
    vector<vector<int>> adjList;
    vector<int> colors;
    int paramP, paramQ;
```
**Linhas 15-20**: Atributos privados da classe:
- `n`: Número de vértices do grafo
- `a`: Número de arestas do grafo
- `adjList`: Lista de adjacências (vetor de vetores), onde `adjList[i]` contém os vizinhos do vértice `i`
- `colors`: Vetor que armazena a cor de cada vértice (-1 indica não colorido)
- `paramP`: Parâmetro p da coloração L(p,q) - distância mínima entre cores de vértices adjacentes
- `paramQ`: Parâmetro q da coloração L(p,q) - distância mínima entre cores de vértices a distância 2

```cpp
public:
    Grafo(int nVertices);
    Grafo(int nVertices, int p, int q);
```
**Linhas 22-24**: Construtores públicos:
- Construtor simples que recebe apenas o número de vértices (usa p=1, q=0 por padrão)
- Construtor que recebe número de vértices e os parâmetros p e q

```cpp
    void addAresta(int u, int v);
    void adicionarAresta(int u, int v);
```
**Linhas 25-26**: Métodos para adicionar arestas:
- `addAresta`: Adiciona uma aresta entre vértices u e v
- `adicionarAresta`: Método alternativo (chama `addAresta`)

```cpp
    int getNumVertices() const;
    int getNumArestas();
    const vector<int>& getVizinhos();
    int getGrau(int u);
```
**Linhas 27-30**: Métodos getters:
- `getNumVertices`: Retorna o número de vértices
- `getNumArestas`: Retorna o número de arestas
- `getVizinhos`: Retorna vetor vazio (método não utilizado)
- `getGrau`: Retorna o grau de um vértice específico

```cpp
    int getColor(int v);
    void setColor(int v, int cor);
```
**Linhas 31-32**: Métodos para manipulação de cores:
- `getColor`: Retorna a cor do vértice v
- `setColor`: Define a cor do vértice v

```cpp
    const vector<vector<int>>& getAdjList() const;
```
**Linha 33**: Retorna a lista de adjacências completa (referência constante para eficiência).

```cpp
    bool corEhSegura(int u, int corTentativa, const vector<int>& coresAtuais);
```
**Linha 34**: Verifica se uma cor é segura para um vértice, considerando as restrições L(p,q):
- Verifica se a diferença de cor com vizinhos diretos é >= p
- Verifica se a diferença de cor com vizinhos de distância 2 é >= q

```cpp
    int obterMenorCorValida(int u, const vector<int>& cores);
```
**Linha 35**: Retorna a menor cor válida (inteiro não-negativo) que pode ser atribuída ao vértice u.

```cpp
    void imprimirSolucaoDOT(const vector<int>& cores, string titulo);
```
**Linha 36**: Imprime a solução em formato DOT (GraphViz) para visualização do grafo colorido.

```cpp
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
```
**Linhas 39-50**: Enumeração de cores (não utilizada diretamente no código, mas disponível para futuras implementações).

---

### Grafo.cpp

Este arquivo contém a implementação dos métodos da classe `Grafo`.

```cpp
#include "Grafo.h"
```
**Linha 1**: Inclui o arquivo header com a definição da classe.

```cpp
Grafo::Grafo(int nVertices)
{
    this->n = nVertices;
    this->a = 0;
    this->paramP = 1;
    this->paramQ = 0;
    this->adjList.resize(n);
    this->colors.assign(n,-1);
}
```
**Linhas 3-11**: Construtor simples:
- **Linha 5**: Inicializa o número de vértices
- **Linha 6**: Inicializa o número de arestas como 0
- **Linha 7**: Define paramP = 1 (padrão)
- **Linha 8**: Define paramQ = 0 (padrão)
- **Linha 9**: Redimensiona a lista de adjacências para n vértices
- **Linha 10**: Inicializa o vetor de cores com -1 (não colorido) para todos os n vértices

```cpp
Grafo::Grafo(int nVertices, int p, int q)
{
    this->n = nVertices;
    this->a = 0;
    this->paramP = p;
    this->paramQ = q;
    this->adjList.resize(n);
    this->colors.assign(n,-1);
}
```
**Linhas 13-21**: Construtor com parâmetros p e q:
- Similar ao construtor anterior, mas permite definir os valores de p e q

```cpp
void Grafo::addAresta(int u, int v)
{
    if( u < 0|| u >= n || v < 0 || v >= n)
    {
        cout << "Erro!" << endl;
        return;
    }
```
**Linhas 23-29**: Início do método `addAresta`:
- **Linha 25**: Validação dos índices dos vértices
- **Linhas 26-28**: Se índices inválidos, imprime erro e retorna

```cpp
    this->adjList[u].push_back(v);
    this->adjList[v].push_back(u);
    this->a++;
}
```
**Linhas 31-34**: Adiciona a aresta ao grafo:
- **Linha 31**: Adiciona v à lista de adjacências de u
- **Linha 32**: Adiciona u à lista de adjacências de v (grafo não-direcionado)
- **Linha 33**: Incrementa o contador de arestas

```cpp
void Grafo::adicionarAresta(int u, int v)
{
    addAresta(u, v);
}
```
**Linhas 36-39**: Método alternativo que simplesmente chama `addAresta`.

```cpp
int Grafo::getNumVertices() const
{
    return this->n;
}
```
**Linhas 41-44**: Retorna o número de vértices do grafo.

```cpp
int Grafo::getNumArestas()
{
    return this->a;
}
```
**Linhas 46-49**: Retorna o número de arestas do grafo.

```cpp
const vector<int>& Grafo::getVizinhos()
{
    static vector<int> empty;
    return empty;
}
```
**Linhas 51-55**: Método não implementado corretamente (retorna vetor vazio estático).

```cpp
int Grafo::getGrau(int u)
{
    if(u >= 0 && u < n){
        return this->adjList[u].size();
    }
    return -1;
}
```
**Linhas 57-62**: Retorna o grau do vértice u:
- **Linha 59**: Valida se u é um índice válido
- **Linha 60**: Retorna o tamanho da lista de adjacências (número de vizinhos)
- **Linha 62**: Retorna -1 se índice inválido

```cpp
int Grafo::getColor(int v)
{
    return this->colors[v];
}
```
**Linhas 64-67**: Retorna a cor atual do vértice v.

```cpp
void Grafo::setColor(int v, int color)
{
    if(v >= 0 && v < n) {
        this->colors[v] = color;
    }
}
```
**Linhas 69-73**: Define a cor do vértice v:
- **Linha 71**: Valida o índice
- **Linha 72**: Atribui a cor

```cpp
const vector<vector<int>>& Grafo::getAdjList() const
{
    return this->adjList;
}
```
**Linhas 75-78**: Retorna referência constante à lista de adjacências completa.

```cpp
bool Grafo::corEhSegura(int u, int corTentativa, const vector<int>& coresAtuais)
{
    for (int vizinho : adjList[u]) {
        if (coresAtuais[vizinho] != -1) {
            if (abs(corTentativa - coresAtuais[vizinho]) < paramP) return false;
        }
```
**Linhas 80-85**: Verifica restrição L(p,q) - Parte 1 (vizinhos diretos):
- **Linha 82**: Itera sobre cada vizinho direto de u
- **Linha 83**: Verifica se o vizinho já foi colorido
- **Linha 84**: Se a diferença absoluta entre as cores é menor que p, a cor não é segura

```cpp
        for (int vizinhoDoVizinho : adjList[vizinho]) {
            if (vizinhoDoVizinho != u && coresAtuais[vizinhoDoVizinho] != -1) {
                if (abs(corTentativa - coresAtuais[vizinhoDoVizinho]) < paramQ) return false;
            }
        }
    }
    return true;
}
```
**Linhas 87-93**: Verifica restrição L(p,q) - Parte 2 (vizinhos a distância 2):
- **Linha 87**: Itera sobre os vizinhos do vizinho (vértices a distância 2)
- **Linha 88**: Verifica se não é o próprio vértice u e se já foi colorido
- **Linha 89**: Se a diferença absoluta entre as cores é menor que q, a cor não é segura
- **Linha 92**: Se passou por todas as verificações, a cor é segura

```cpp
int Grafo::obterMenorCorValida(int u, const vector<int>& cores)
{
    int cor = 0;
    while (!corEhSegura(u, cor, cores)) {
        cor++;
    }
    return cor;
}
```
**Linhas 95-101**: Encontra a menor cor válida:
- **Linha 97**: Começa com cor 0
- **Linha 98**: Enquanto a cor não for segura, incrementa
- **Linha 99**: Incrementa a cor
- **Linha 101**: Retorna a primeira cor válida encontrada

```cpp
void Grafo::imprimirSolucaoDOT(const vector<int>& cores, string titulo)
{
    cout << "// " << titulo << "\n";
    cout << "graph G {\n";
    cout << "  node [style=filled, fontname=\"Arial\"];\n";
```
**Linhas 103-107**: Início da impressão em formato DOT:
- **Linha 105**: Imprime comentário com título
- **Linha 106**: Inicia definição do grafo
- **Linha 107**: Define estilo dos nós

```cpp
    for (int i = 0; i < n; ++i) {
        cout << "  " << i << " [label=\"" << i << "\\n(Cor " << cores[i] << ")\"";
        cout << ", fillcolor=\"/set312/" << (cores[i] % 12 + 1) << "\"];\n";
    }
```
**Linhas 108-111**: Imprime definição de cada vértice:
- **Linha 108**: Itera sobre todos os vértices
- **Linha 109**: Define o rótulo do vértice (número e cor)
- **Linha 110**: Define a cor de preenchimento usando paleta set312 do GraphViz

```cpp
    for (int u = 0; u < n; ++u) {
        for (int v : adjList[u]) {
            if (u < v) {
                cout << "  " << u << " -- " << v << ";\n";
            }
        }
    }
    cout << "}\n\n";
}
```
**Linhas 112-119**: Imprime as arestas:
- **Linha 112**: Itera sobre todos os vértices
- **Linha 113**: Itera sobre os vizinhos
- **Linha 114**: Condição `u < v` garante que cada aresta seja impressa apenas uma vez
- **Linha 115**: Imprime a aresta no formato DOT
- **Linha 118**: Fecha a definição do grafo

---

### Algoritimos.h

Este arquivo define a classe `Algoritimos` que implementa os algoritmos de coloração.

```cpp
#ifndef TRABALHO_DCC059_ALGORITIMOS_H
#define TRABALHO_DCC059_ALGORITIMOS_H
```
**Linhas 1-2**: Guards de inclusão.

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Grafo.h"
```
**Linhas 4-9**: Inclusão de bibliotecas e do header Grafo.

```cpp
using namespace std;
```
**Linha 11**: Declaração do namespace padrão.

```cpp
class Algoritimos {
```
**Linha 13**: Declaração da classe `Algoritimos`.

```cpp
private:
    Grafo* grafo;  // Ponteiro para o grafo a ser colorido
```
**Linhas 15-16**: Atributo privado:
- `grafo`: Ponteiro para o objeto Grafo que será colorido

```cpp
public:
    Algoritimos(Grafo* g);
    ~Algoritimos();
```
**Linhas 18-20**: Construtor e destrutor públicos:
- Construtor recebe ponteiro para Grafo
- Destrutor para liberar recursos

```cpp
    // Algoritmo Guloso (Determinístico - Ordenado por Grau)
    vector<int> guloso(unsigned semente = 0);
```
**Linhas 22-23**: Método `guloso`:
- Implementa algoritmo guloso determinístico
- Ordena vértices por grau decrescente
- Parâmetro `semente` não é utilizado nesta versão

```cpp
    // Algoritmo Guloso Randomizado
    vector<int> gulosoRandomizado(unsigned semente = 42);
```
**Linhas 25-26**: Método `gulosoRandomizado`:
- Implementa algoritmo guloso com ordem aleatória
- `semente`: Define a semente para o gerador aleatório (padrão = 42)

```cpp
    // Algoritmo Guloso Randomizado Reativo (Iterativo)
    vector<int> gulosoReativo(int iteracoes = 100);
```
**Linhas 28-29**: Método `gulosoReativo`:
- Executa múltiplas iterações do guloso randomizado
- Retorna a melhor solução encontrada
- `iteracoes`: Número de tentativas (padrão = 100)

---

### Algoritimos.cpp

Este arquivo contém a implementação dos algoritmos de coloração.

```cpp
#include "Algoritimos.h"
```
**Linha 1**: Inclui o header da classe.

```cpp
Algoritimos::Algoritimos(Grafo* g)
{
    this->grafo = g;
}
```
**Linhas 3-6**: Construtor:
- **Linha 5**: Armazena o ponteiro para o grafo

```cpp
Algoritimos::~Algoritimos()
{
}
```
**Linhas 8-10**: Destrutor vazio (não há alocação dinâmica para liberar).

```cpp
vector<int> Algoritimos::guloso(unsigned semente)
{
    int n = grafo->getNumVertices();
    const auto& adjList = grafo->getAdjList();
```
**Linhas 12-15**: Início do algoritmo guloso:
- **Linha 14**: Obtém o número de vértices
- **Linha 15**: Obtém referência à lista de adjacências

```cpp
    vector<int> ordemVertices(n);
    for(int i = 0; i < n; ++i) {
        ordemVertices[i] = i;
    }
```
**Linhas 17-20**: Cria vetor com índices dos vértices:
- **Linha 17**: Cria vetor de tamanho n
- **Linhas 18-20**: Preenche com 0, 1, 2, ..., n-1

```cpp
    sort(ordemVertices.begin(), ordemVertices.end(), [&](int a, int b) {
        return adjList[a].size() > adjList[b].size();
    });
```
**Linhas 21-23**: Ordena vértices por grau decrescente:
- **Linha 21**: Usa `sort` com função lambda
- **Linha 22**: Compara tamanhos das listas de adjacências (graus)
- Vértices com maior grau vêm primeiro

```cpp
    vector<int> cores(n, -1);
    for (int u : ordemVertices) {
        cores[u] = grafo->obterMenorCorValida(u, cores);
    }
    
    return cores;
}
```
**Linhas 25-30**: Coloração gulosa:
- **Linha 25**: Cria vetor de cores inicializado com -1
- **Linha 26**: Itera sobre vértices na ordem definida
- **Linha 27**: Para cada vértice, atribui a menor cor válida
- **Linha 30**: Retorna o vetor de cores resultante

```cpp
vector<int> Algoritimos::gulosoRandomizado(unsigned semente)
{
    int n = grafo->getNumVertices();
    
    vector<int> ordemVertices(n);
    for(int i = 0; i < n; ++i) {
        ordemVertices[i] = i;
    }
```
**Linhas 32-39**: Início do algoritmo guloso randomizado:
- Similar ao guloso, mas sem ordenação por grau
- **Linha 34**: Obtém número de vértices
- **Linhas 36-39**: Cria vetor com índices dos vértices

```cpp
    mt19937 gerador(semente);
    shuffle(ordemVertices.begin(), ordemVertices.end(), gerador);
```
**Linhas 40-41**: Embaralha a ordem dos vértices:
- **Linha 40**: Cria gerador Mersenne Twister com a semente fornecida
- **Linha 41**: Embaralha aleatoriamente o vetor de vértices

```cpp
    vector<int> cores(n, -1);
    for (int u : ordemVertices) {
        cores[u] = grafo->obterMenorCorValida(u, cores);
    }
    
    return cores;
}
```
**Linhas 43-48**: Coloração gulosa com ordem aleatória:
- Idêntico ao algoritmo guloso, mas usa ordem embaralhada

```cpp
vector<int> Algoritimos::gulosoReativo(int iteracoes)
{
    int n = grafo->getNumVertices();
    
    vector<int> melhoresCores;
    int menorMaiorCor = 1e9;
```
**Linhas 50-55**: Início do algoritmo guloso reativo:
- **Linha 52**: Obtém número de vértices
- **Linha 54**: Vetor para armazenar a melhor solução
- **Linha 55**: Inicializa menor número de cores encontrado com valor muito alto (10^9)

```cpp
    unsigned sementeBase = chrono::system_clock::now().time_since_epoch().count();
```
**Linha 56**: Gera semente base usando tempo atual do sistema.

```cpp
    for (int i = 0; i < iteracoes; ++i) {
        vector<int> ordemVertices(n);
        for(int j = 0; j < n; ++j) {
            ordemVertices[j] = j;
        }
```
**Linhas 58-62**: Loop principal de iterações:
- **Linha 58**: Executa o número especificado de iterações
- **Linhas 59-62**: Cria vetor de vértices para cada iteração

```cpp
        mt19937 gerador(sementeBase + i);
        shuffle(ordemVertices.begin(), ordemVertices.end(), gerador);
```
**Linhas 64-65**: Embaralha vértices com semente única:
- **Linha 64**: Cria gerador com semente diferente para cada iteração (sementeBase + i)
- **Linha 65**: Embaralha a ordem dos vértices

```cpp
        vector<int> coresAtuais(n, -1);
        for (int u : ordemVertices) {
            coresAtuais[u] = grafo->obterMenorCorValida(u, coresAtuais);
        }
```
**Linhas 67-70**: Coloração gulosa para esta iteração:
- **Linha 67**: Cria vetor de cores para esta tentativa
- **Linhas 68-70**: Colore todos os vértices na ordem embaralhada

```cpp
        int maiorCorNessaTentativa = -1;
        for(int c : coresAtuais) {
            if(c > maiorCorNessaTentativa) maiorCorNessaTentativa = c;
        }
```
**Linhas 71-74**: Encontra o número cromático desta tentativa:
- **Linha 71**: Inicializa com -1
- **Linha 72**: Itera sobre todas as cores atribuídas
- **Linha 73**: Atualiza se encontrar cor maior
- Resultado: a maior cor usada indica o número de cores necessárias

```cpp
        if (maiorCorNessaTentativa < menorMaiorCor) {
            menorMaiorCor = maiorCorNessaTentativa;
            melhoresCores = coresAtuais;
        }
    }
```
**Linhas 75-78**: Atualiza melhor solução se necessário:
- **Linha 75**: Se esta tentativa usou menos cores
- **Linha 76**: Atualiza o menor número de cores encontrado
- **Linha 77**: Salva esta coloração como a melhor
- **Linha 79**: Fim do loop de iterações

```cpp
    return melhoresCores;
}
```
**Linhas 81-82**: Retorna a melhor coloração encontrada entre todas as iterações.

---

### Utils.h

Este arquivo define a classe utilitária `Utils` para operações auxiliares.

```cpp
#ifndef TRABALHO_DCC059_UTILS_H
#define TRABALHO_DCC059_UTILS_H
```
**Linhas 1-2**: Guards de inclusão.

```cpp
#include<fstream>
#include<cstring>
#include "Grafo.h"
```
**Linhas 4-6**: Inclusão de bibliotecas:
- `fstream`: Para leitura de arquivos
- `cstring`: Para manipulação de strings C
- `Grafo.h`: Header da classe Grafo

```cpp
class Utils
{
private:

public:
    Utils();
    ~Utils();
```
**Linhas 9-15**: Declaração da classe Utils:
- Seção privada vazia
- Construtor e destrutor públicos

```cpp
    static Grafo* readAndCreate(string filePath, int p = 2, int q = 1);
};
```
**Linhas 17-18**: Método estático `readAndCreate`:
- `filePath`: Caminho do arquivo a ser lido
- `p`: Parâmetro p da coloração L(p,q) (padrão = 2)
- `q`: Parâmetro q da coloração L(p,q) (padrão = 1)
- Retorna ponteiro para novo objeto Grafo criado a partir do arquivo

---

### Utils.cpp

Este arquivo implementa a funcionalidade de leitura de grafos de arquivos.

```cpp
#include "Utils.h"
```
**Linha 1**: Inclui o header da classe.

```cpp
Utils::Utils()
{

}
```
**Linhas 4-7**: Construtor vazio.

```cpp
Utils::~Utils()
{
}
```
**Linhas 9-11**: Destrutor vazio.

```cpp
Grafo *Utils::readAndCreate(string filePath, int p, int q)
{
    ifstream inFile;

    inFile.open(filePath, ios::in);
```
**Linhas 15-19**: Início do método de leitura:
- **Linha 17**: Cria objeto ifstream para leitura
- **Linha 19**: Abre o arquivo especificado para leitura

```cpp
    if (!inFile)
    {
        cout << "Erro, Arquivo não encontrado" << endl;
        return nullptr;
    }
```
**Linhas 21-25**: Validação da abertura do arquivo:
- **Linha 21**: Verifica se arquivo foi aberto com sucesso
- **Linha 23**: Imprime mensagem de erro
- **Linha 24**: Retorna nullptr se falhou

```cpp
    string l, trash;
    int numVertices, numArestas, u, v;
    numVertices = numArestas = u = v = 0;
    Grafo *grafo = nullptr;
```
**Linhas 27-30**: Declaração de variáveis:
- `l`: String para armazenar cada linha lida
- `trash`: String para descartar palavras não necessárias
- `numVertices`, `numArestas`, `u`, `v`: Variáveis inteiras para dados do grafo
- **Linha 29**: Inicializa todas com 0
- **Linha 30**: Ponteiro para o grafo a ser criado

```cpp
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
```
**Linhas 32-44**: Lê cabeçalho do arquivo:
- **Linha 32**: Loop que lê linha por linha
- **Linha 35**: Verifica se linha começa com 'p' (linha de problema)
- **Linha 37**: Cria stringstream para parsing da linha
- **Linhas 38-39**: Descarta as duas primeiras palavras ("p" e tipo do problema)
- **Linha 40**: Lê número de vértices
- **Linha 41**: Lê número de arestas
- **Linha 42**: Sai do loop após processar linha 'p'

```cpp
    grafo = new Grafo(numVertices, p, q);
    cout << "Grafo criado com " << numVertices << " Vertices." << endl;
```
**Linhas 46-47**: Cria o grafo:
- **Linha 46**: Aloca novo objeto Grafo com os parâmetros lidos
- **Linha 47**: Confirma criação do grafo

```cpp
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
```
**Linhas 49-58**: Lê as arestas:
- **Linha 49**: Loop que lê as linhas restantes
- **Linha 51**: Verifica se linha começa com 'e' (linha de aresta)
- **Linha 52**: Cria stringstream para parsing
- **Linha 53**: Descarta a letra 'e'
- **Linha 54**: Lê primeiro vértice
- **Linha 55**: Lê segundo vértice
- **Linha 56**: Adiciona aresta (subtrai 1 pois arquivos usam índices 1-based, código usa 0-based)

```cpp
    inFile.close();

    return grafo;
}
```
**Linhas 59-62**: Finalização:
- **Linha 59**: Fecha o arquivo
- **Linha 61**: Retorna o ponteiro para o grafo criado

---

### main.cpp

Este arquivo contém o ponto de entrada do programa e os testes dos algoritmos.

```cpp
#include "Grafo.h"
#include "Utils.h"
#include "Algoritimos.h"
#include <iostream>
#include <iomanip>
```
**Linhas 1-5**: Inclusão de headers:
- Headers das classes do projeto
- `iostream`: Entrada/saída
- `iomanip`: Formatação de saída

```cpp
using namespace std;
```
**Linha 7**: Declaração do namespace padrão.

```cpp
bool validarColorcao(const Grafo* g, const vector<int>& cores) {
    const auto& adjList = g->getAdjList();
    int n = g->getNumVertices();
```
**Linhas 9-11**: Função de validação - início:
- Recebe ponteiro para grafo e vetor de cores
- **Linha 10**: Obtém lista de adjacências
- **Linha 11**: Obtém número de vértices

```cpp
    for (int u = 0; u < n; ++u) {
        for (int v : adjList[u]) {
            if (cores[u] == cores[v]) {
                return false;
            }
        }
    }
    return true;
}
```
**Linhas 13-20**: Validação da coloração:
- **Linha 13**: Itera sobre todos os vértices
- **Linha 14**: Itera sobre vizinhos de cada vértice
- **Linha 15**: Verifica se vértices adjacentes têm a mesma cor
- **Linha 16**: Se sim, coloração é inválida
- **Linha 20**: Se passou por todos, coloração é válida

**Nota**: Esta função valida apenas coloração tradicional, não verifica restrições L(p,q).

```cpp
int contarCoresUsadas(const vector<int>& cores) {
    int maxCor = 0;
    for (int c : cores) {
        maxCor = max(maxCor, c);
    }
    return maxCor + 1;
}
```
**Linhas 22-28**: Conta número de cores usadas:
- **Linha 23**: Inicializa com 0
- **Linha 24**: Itera sobre todas as cores
- **Linha 25**: Mantém track da maior cor encontrada
- **Linha 27**: Retorna maior cor + 1 (pois cores começam em 0)

```cpp
void executarTeste(const string& nomeTeste, bool resultado) {
    cout << "[" << (resultado ? "PASS" : "FAIL") << "] " << nomeTeste << endl;
}
```
**Linhas 30-32**: Função auxiliar de teste:
- **Linha 31**: Imprime [PASS] ou [FAIL] seguido do nome do teste

```cpp
void testarAlgoritmo(const Grafo* g, const vector<int>& resultado, const string& nomeAlgoritmo) {
    bool valido = validarColorcao(g, resultado);
    int numCores = contarCoresUsadas(resultado);
    
    executarTeste(nomeAlgoritmo + " - Coloração válida", valido);
    cout << "        Cores usadas: " << numCores << endl;
}
```
**Linhas 34-39**: Função de teste de algoritmo:
- **Linha 35**: Valida a coloração
- **Linha 36**: Conta cores usadas
- **Linha 38**: Executa teste de validação
- **Linha 39**: Imprime número de cores

```cpp
int main() {
    int p = 2, q = 1;
```
**Linhas 41-42**: Início do main:
- Define parâmetros da coloração L(2,1)

```cpp
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
```
**Linhas 44-53**: Criação do grafo de teste:
- **Linha 44**: Cria grafo com 6 vértices
- **Linha 45**: Cria objeto Grafo
- **Linhas 46-53**: Adiciona 8 arestas formando um grafo específico

```cpp
    Algoritimos algo(&meuGrafo);
```
**Linha 54**: Cria objeto Algoritimos passando referência ao grafo.

```cpp
    cout << "\n=== TESTES DOS ALGORITMOS DE COLORAÇÃO ===" << endl;
    cout << "Parâmetros: L(" << p << "," << q << ")" << endl;
    cout << "Vertices: " << meuGrafo.getNumVertices() << endl;
    cout << "Arestas: " << meuGrafo.getNumArestas() << endl;
    cout << "\n--- Executando testes ---\n" << endl;
```
**Linhas 56-60**: Imprime informações do teste:
- **Linha 56**: Cabeçalho
- **Linha 57**: Parâmetros L(p,q)
- **Linha 58**: Número de vértices
- **Linha 59**: Número de arestas
- **Linha 60**: Separador

```cpp
    vector<int> guloso_result = algo.guloso();
    testarAlgoritmo(&meuGrafo, guloso_result, "Guloso");
```
**Linhas 62-63**: Testa algoritmo guloso:
- **Linha 62**: Executa algoritmo guloso
- **Linha 63**: Valida e imprime resultados

```cpp
    vector<int> randomizado_result = algo.gulosoRandomizado(42);
    testarAlgoritmo(&meuGrafo, randomizado_result, "Guloso Randomizado");
```
**Linhas 65-66**: Testa algoritmo guloso randomizado:
- Usa semente 42 para reprodutibilidade

```cpp
    int iteracoes = 100;
    vector<int> reativo_result = algo.gulosoReativo(iteracoes);
    testarAlgoritmo(&meuGrafo, reativo_result, "Guloso Reativo (" + to_string(iteracoes) + " iterações)");
```
**Linhas 68-70**: Testa algoritmo guloso reativo:
- **Linha 68**: Define 100 iterações
- **Linha 69**: Executa algoritmo
- **Linha 70**: Valida e imprime resultados

```cpp
    int max_guloso = contarCoresUsadas(guloso_result);
    int max_randomizado = contarCoresUsadas(randomizado_result);
    int max_reativo = contarCoresUsadas(reativo_result);
```
**Linhas 72-74**: Conta cores de cada algoritmo:
- Armazena número de cores usadas por cada método

```cpp
    cout << "\n--- Validação geral ---\n" << endl;
    executarTeste("Todas as colorações são válidas", 
                  validarColorcao(&meuGrafo, guloso_result) && 
                  validarColorcao(&meuGrafo, randomizado_result) && 
                  validarColorcao(&meuGrafo, reativo_result));
```
**Linhas 76-80**: Validação geral:
- Verifica se todos os três algoritmos produziram colorações válidas

```cpp
    cout << "\n=== RESULTADOS COMPARATIVOS ===" << endl;
    cout << setw(30) << "Algoritmo" << setw(15) << "Cores Usadas" << endl;
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    cout << setw(30) << "Guloso" << setw(15) << max_guloso << endl;
    cout << setw(30) << "Guloso Randomizado" << setw(15) << max_randomizado << endl;
    cout << setw(30) << "Guloso Reativo (100 it.)" << setw(15) << max_reativo << endl;
```
**Linhas 82-87**: Tabela comparativa:
- **Linha 82**: Cabeçalho
- **Linha 83**: Colunas da tabela
- **Linha 84**: Linha separadora
- **Linhas 85-87**: Resultados de cada algoritmo formatados

```cpp
    int melhor = min({max_guloso, max_randomizado, max_reativo});
    cout << "\n--- Conclusão ---\n" << endl;
    cout << "Melhor resultado: " << melhor << " cores" << endl;
```
**Linhas 89-91**: Identifica melhor resultado:
- **Linha 89**: Encontra o mínimo entre os três
- **Linha 91**: Imprime o melhor resultado

```cpp
    if (melhor == max_reativo) {
        cout << "Vencedor: Guloso Reativo" << endl;
    } else if (melhor == max_randomizado) {
        cout << "Vencedor: Guloso Randomizado" << endl;
    } else {
        cout << "Vencedor: Guloso (Determinístico)" << endl;
    }
```
**Linhas 92-98**: Anuncia o vencedor:
- Verifica qual algoritmo obteve o menor número de cores
- Imprime o nome do algoritmo vencedor

```cpp
    cout << "\n=== SOLUÇÃO GULOSO EM DOT ===" << endl;
    meuGrafo.imprimirSolucaoDOT(guloso_result, "Solucao Guloso");
    
    return 0;
}
```
**Linhas 100-104**: Finalização:
- **Linha 100**: Cabeçalho para saída DOT
- **Linha 101**: Imprime grafo colorido em formato DOT (GraphViz)
- **Linha 103**: Retorna 0 indicando execução bem-sucedida

---

## Resumo dos Algoritmos Implementados

### 1. Algoritmo Guloso Determinístico
- **Estratégia**: Ordena vértices por grau decrescente
- **Complexidade**: O(n log n + n²) no pior caso
- **Vantagens**: Determinístico, resultados consistentes
- **Desvantagens**: Pode não encontrar solução ótima

### 2. Algoritmo Guloso Randomizado
- **Estratégia**: Processa vértices em ordem aleatória
- **Complexidade**: O(n² + shuffle)
- **Vantagens**: Diversidade de soluções
- **Desvantagens**: Resultados variam, não garante melhor que determinístico

### 3. Algoritmo Guloso Reativo
- **Estratégia**: Executa múltiplas iterações randomizadas e seleciona melhor
- **Complexidade**: O(k × n²) onde k = número de iterações
- **Vantagens**: Melhores resultados pela exploração do espaço de soluções
- **Desvantagens**: Mais custoso computacionalmente

---

## Restrições L(p,q) Implementadas

O projeto implementa coloração com restrições L(p,q):

- **Parâmetro p**: Diferença mínima entre cores de vértices adjacentes
  - `|cor(u) - cor(v)| ≥ p` para toda aresta (u,v)

- **Parâmetro q**: Diferença mínima entre cores de vértices a distância 2
  - `|cor(u) - cor(w)| ≥ q` para todo par (u,w) com distância 2

---

## Formato de Arquivo de Entrada

O programa lê grafos no formato DIMACS:

```
c Comentários começam com 'c'
p edge <num_vertices> <num_arestas>
e <vertice1> <vertice2>
e <vertice1> <vertice3>
...
```

**Exemplo**:
```
c Grafo simples de teste
p edge 5 6
e 1 2
e 1 3
e 2 3
e 2 4
e 3 5
e 4 5
```

---

## Saída em Formato DOT

O programa gera saída em formato GraphViz DOT para visualização:

```dot
graph G {
  node [style=filled, fontname="Arial"];
  0 [label="0\n(Cor 0)", fillcolor="/set312/1"];
  1 [label="1\n(Cor 2)", fillcolor="/set312/3"];
  ...
  0 -- 2;
  0 -- 4;
  ...
}
```

Para visualizar, salve em arquivo `.dot` e use:
```bash
dot -Tpng grafo.dot -o grafo.png
```

---

## Compilação e Execução

### Usando CMake:
```bash
cd build
cmake ..
cmake --build .
./Trabalho_DCC059
```

### Usando Task do VS Code:
- Pressione `Ctrl+Shift+B` e selecione "Build"
- Ou use `Ctrl+Shift+P` → "Tasks: Run Build Task"

---

## Estrutura de Classes - Diagrama

```
┌────────────────────────────────────────┐
│             Grafo                       │
├────────────────────────────────────────┤
│ - n: int                               │
│ - a: int                               │
│ - adjList: vector<vector<int>>         │
│ - colors: vector<int>                  │
│ - paramP, paramQ: int                  │
├────────────────────────────────────────┤
│ + Grafo(int)                           │
│ + Grafo(int, int, int)                 │
│ + addAresta(int, int): void            │
│ + getNumVertices(): int                │
│ + getNumArestas(): int                 │
│ + getGrau(int): int                    │
│ + getColor(int): int                   │
│ + setColor(int, int): void             │
│ + getAdjList(): vector<vector<int>>&   │
│ + corEhSegura(int, int, vec): bool     │
│ + obterMenorCorValida(int, vec): int   │
│ + imprimirSolucaoDOT(vec, str): void   │
└────────────────────────────────────────┘
              △
              │
              │ usa
              │
┌─────────────┴──────────────────────────┐
│          Algoritimos                    │
├────────────────────────────────────────┤
│ - grafo: Grafo*                        │
├────────────────────────────────────────┤
│ + Algoritimos(Grafo*)                  │
│ + guloso(): vector<int>                │
│ + gulosoRandomizado(unsigned): vec     │
│ + gulosoReativo(int): vector<int>      │
└────────────────────────────────────────┘


┌────────────────────────────────────────┐
│             Utils                       │
├────────────────────────────────────────┤
│                                        │
├────────────────────────────────────────┤
│ + readAndCreate(string, int, int):     │
│                           Grafo*       │
└────────────────────────────────────────┘
```

---

## Considerações Finais

Este projeto demonstra a implementação de algoritmos heurísticos para o problema de coloração L(p,q) em grafos. Os três algoritmos implementados oferecem diferentes trade-offs entre qualidade de solução e tempo de execução.

O código está bem estruturado, com separação clara de responsabilidades:
- **Grafo**: Estrutura de dados e validações
- **Algoritimos**: Heurísticas de coloração
- **Utils**: Operações de I/O
- **main**: Testes e comparações

A documentação linha a linha permite compreensão completa da implementação e facilita futuras manutenções e extensões do código.
