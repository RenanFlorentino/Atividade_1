#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::vector;

#define INFINITO 9999999
#define BRANCO 0
#define CINZA 1
#define PRETO 2

class Grafo
{
private:
    int numVertices; // Numero de vertices

    vector<vector<int>> matrizAdjacencia; // Matriz de adjacencia
    vector<vector<int>> listaAdjacencia;  // Lista de adjacencia
    vector<int> pais;                     // Lista de pais e distancia entre os vertices
    vector<int> distancia;
    vector<int> Cor; // Lista de vertices visitados

public:
    // Construtor
    Grafo(int numVertices = 0)
    {
        setNumVertices(numVertices);

        // Inicializa a matriz de adjacencia
        for (int i = 0; i < numVertices; i++)
        {
            vector<int> linha;
            vector<int> vertice;

            for (int j = 0; j < numVertices; j++)
            {
                linha.push_back(0);
            }
            // vertice.push_back(i);

            matrizAdjacencia.push_back(linha);
            listaAdjacencia.push_back(vertice);
            Cor.push_back(BRANCO);
            distancia.push_back(INFINITO);
            pais.push_back(-1);
        }
    }

    // Destrutor
    ~Grafo()
    {
        // Destroi a matriz de adjacencia
        for (int i = 0; i < numVertices; i++)
        {
            matrizAdjacencia[i].clear();
            listaAdjacencia[i].clear();
        }
        matrizAdjacencia.clear();
        listaAdjacencia.clear();
        Cor.clear();
        distancia.clear();
        pais.clear();
    }

    // Metodos de acesso e modificacao

    void setNumVertices(int numVertices)
    {
        this->numVertices = numVertices;
    }
    int getNumVertices()
    {
        return numVertices;
    }

    void setMatrizAdjacencia(int i, int j, int peso)
    {
        matrizAdjacencia[i][j] = peso;
    }
    int getMatrizAdjacencia(int i, int j)
    {
        return matrizAdjacencia[i][j];
    }

    void setListaAdjacencia(int i, int j)
    {
        listaAdjacencia[i].push_back(j);
    }
    int getListaAdjacencia(int i, int j)
    {
        return listaAdjacencia[i][j];
    }

    void setCor(int i, int cor)
    {
        Cor[i] = cor;
    }
    int getCor(int i)
    {
        return Cor[i];
    }

    void setDistancia(int i, int distancia)
    {
        this->distancia[i] = distancia;
    }
    int getDistancia(int i)
    {
        return distancia[i];
    }

    void setPais(int i, int pais)
    {
        this->pais[i] = pais;
    }
    int getPais(int i)
    {
        return pais[i];
    }

    /// Metodos de manipulacao do grafo
    int ComponentesConexas()
    {

        int cont = 0;
        for (int i = 0; i < numVertices; i++)
        {
            if (pais[i] == -1)
            {
                cont++;
            }
        }
        return cont;
    }
    void imprime()
    {

        cout << "Numero de vertices: " << numVertices << endl;
        cout << "Matriz de adjacencia: " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                cout << matrizAdjacencia[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Lista de adjacencia: " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " -> ";
            for (int j = 0; j < listaAdjacencia[i].size(); j++)
            {
                cout << listaAdjacencia[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Lista de cores: " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " -> " << Cor[i] << endl;
        }

        cout << "Lista de distancias: " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " -> " << distancia[i] << endl;
        }

        cout << "Lista de pais: " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " -> " << pais[i] << endl;
        }
    }
    void BFS(int s)
    {

        Cor[s] = CINZA;
        distancia[s] = 0;
        pais[s] = -1;

        queue<int> fila; // Fila de vertices
        fila.push(s);

        while (!fila.empty())
        {

            int v = fila.front(); // Vertice v recebe o primeiro elemento da fila
            fila.pop();           // Remove o primeiro elemento da fila

            for (int i = 0; i < listaAdjacencia[v].size(); i++)
            {

                int u = listaAdjacencia[v][i];

                if (Cor[u] == BRANCO)
                {

                    Cor[u] = CINZA;
                    distancia[u] = distancia[v] + 1;
                    pais[u] = v;
                    fila.push(u);
                }
            }
            Cor[v] = PRETO;
        }
    }
    void caminho()
    {

        // percorre o vetor pais e imprime o caminho

        // 1- acha o vertice de maior distancia

        int maior = 0;
        int vertice = 0;

        for (int i = 0; i < numVertices; i++)
        {
            if (distancia[i] > maior)
            {
                maior = distancia[i];
                vertice = i;
            }
        }

        // 2- imprime o caminho
        cout << "Caminho: " << endl;
        while (vertice != -1)
        {
            cout << "--> " << vertice << " ";
            vertice = pais[vertice];
        }
    }
    void rota(int s, int t)
    {
        /*Criar uma função que imprima o caminho entre dois vértices s e t formado pelo BFS.
         Indicar que “não há caminho entre os vértices” caso não haja o caminho.*/

        BFS(s);
        cout << "Caminho entre " << s << " e " << t << ": ";
        while (t != -1)
        {

            cout << t << " ->"
                 << " ";
            t = pais[t];
        }
    }

    /*
    7.2. Busca em profundidade 𝐷𝐹𝑆 (𝐺)
    1  𝒇𝒐𝒓 cada vértice de 𝑢∈𝑉[𝐺]
    2       𝒅𝒐 𝑐𝑜𝑟[𝑢]←𝐵𝑅𝐴𝑁𝐶𝑂
    3              𝜋[𝑢]←𝑁𝑈𝐿𝐿
    4  𝒇𝒐𝒓 cada vértice de 𝑢∈𝑉[𝐺]
    5       𝒅𝒐 𝑖𝑓 𝑐𝑜𝑟[𝑢]=𝐵𝑅𝐴𝑁𝐶𝑂
    6             𝑡ℎ𝑒𝑛 𝐷𝐹𝑆−𝑉𝐼𝑆𝐼𝑇(𝑢)
    𝐷𝐹𝑆−𝑉𝐼𝑆𝐼𝑇 (𝑢)
    1  𝑐𝑜𝑟[𝑢]←𝐶𝐼𝑁𝑍𝐴
    2  𝒇𝒐𝒓 cada vértice 𝑣∈𝑎𝑑𝑗[𝑢]
    3       𝒅𝒐 𝑖𝑓 𝑐𝑜𝑟[𝑢]=𝐵𝑅𝐴𝑁𝐶𝑂
    4            𝒕𝒉𝒆𝒏 𝜋[𝑣]←𝑢
    5            𝐷𝐹𝑆−𝑉𝐼𝑆𝐼𝑇(𝑣)
    6  𝑐𝑜𝑟[𝑢]←𝑃𝑅𝐸𝑇𝑂

    */

    void DFS()
    {

        // 𝒇𝒐𝒓 cada vértice de 𝑢∈𝑉[𝐺]

        for (int u = 0; u < numVertices; u++)
        {
            Cor[u] = BRANCO;
            pais[u] = -1;
        }

        // 𝒇𝒐𝒓 cada vértice de 𝑢∈𝑉[𝐺]
        for (int u = 0; u < numVertices; u++)
        {
            if (Cor[u] == BRANCO)
            {
                DFS_VISIT(u);
            }
        }
    }
    void DFS_VISIT(int u)
    {

        Cor[u] = CINZA;
        for (int i = 0; i < listaAdjacencia[u].size(); i++)
        {
            int v = listaAdjacencia[u][i];
            if (Cor[v] == BRANCO)
            {
                pais[v] = u;
                DFS_VISIT(v);
            }
        }
    }
    void iterativeDFS()
    {
        queue<int> pilha;

        for (int i = 0; i < numVertices; i++) // 𝒇𝒐𝒓 cada vértice de 𝑢∈𝑉[𝐺]
        {
            if (Cor[i] == BRANCO)
            {
                Cor[i] = CINZA;
                pilha.push(i);
                while (!pilha.empty()) // Verifica se a pilha esta vazia
                {
                    // POP de c++
                    int u = pilha.front();
                    pilha.pop();

                    for (int j = 0; j < listaAdjacencia[u].size(); j++)
                    {
                        int v = listaAdjacencia[u][j];
                        if (Cor[v] == BRANCO)
                        {
                            Cor[v] = CINZA;
                            pais[v] = u;
                            pilha.push(v);
                        }
                    }
                    Cor[u] = PRETO;
                }
            }
        }
    }
};

Grafo readTxt(string nomeArquivo)
{

    FILE *arquivo;
    arquivo = fopen(nomeArquivo.c_str(), "r");

    if (arquivo == NULL)
    {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    int numVertices, valores;
    fscanf(arquivo, "%d", &numVertices);

    Grafo g(numVertices);
    g.imprime();

    // Inicializa a matriz de adjacencia
    for (int i = 0; i < numVertices; i++)
    {

        for (int j = 0; j < numVertices; j++)
        {
            fscanf(arquivo, "%d", &valores);

            if (valores != 0)
            {
                g.setMatrizAdjacencia(i, j, valores);
                g.setListaAdjacencia(i, j);
            }
        }
    }

    fclose(arquivo);

    return g;
}

int main()
{

    
    Grafo g1, g2, g3;

    g1 = readTxt("pcv4.txt");
    g2 = readTxt("pcv10.txt");
    g3 = readTxt("pcv10.txt");


    // Retorno Iterativo DFS
    cout << "Iterative DFS: " << endl;
    g1.iterativeDFS();
    g1.imprime();




    
    cout << "Grafo 1: " << endl;
    g1.imprime();
    cout << "Grafo 2: " << endl;
    g2.imprime();
    cout << "Grafo 3: " << endl;
    g3.imprime();
    
    cout<<"Operações com o Grafo 1: "<<endl;
    g1.BFS(0);
    g1.caminho();
    cout<<endl;
    g1.imprime();
    cout<<endl;
    g1.rota(0,3);
    cout<<endl;
    g1.ComponentesConexas();
    cout<<"Iterative DFS: "<<endl; 
    g1.iterativeDFS();
    
    cout<<"Operações com o Grafo 2: "<<endl;
    g2.DFS();
    g2.imprime();
    cout<<endl;
    g2.ComponentesConexas();

    cout<<"Operações com o Grafo 3: "<<endl;
    g3.iterativeDFS();
    g3.imprime();
    g3.ComponentesConexas();

    
    return 0;
}
