#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>

using namespace std;

struct Vertice {
    set<int> adjacencias;
};


int BFS(vector<Vertice>& grafo, int s, vector<int>& visitados) {
    queue<pair<int, int>> fila;
    int total_visitas = 1; // inicializa o número total de visitas como 1 (pois ele começa visitando o vértice inicial)
    
    fila.emplace(s, 0);
    visitados[s] = 1; // marca o vértice como visitado

    
    while (!fila.empty()) {
        int u = fila.front().first;
        int nivel = fila.front().second;
        fila.pop();

        for (auto v : grafo[u].adjacencias) {
            if (visitados[v] == 0) { // se o vértice ainda não foi visitado
                fila.emplace(v, nivel + 1);
                visitados[v] = nivel + 1; // marca o vértice como visitado
                ++total_visitas; // incrementa o número total de visitas
            }
        }
    }

    return total_visitas;
}


long long int BFS_grafo_desconexo(vector<Vertice>& grafo, long long int B, long long int E) {
    int N = grafo.size();
    vector<int> visitados(N, 0);
    int total_arestas = 0;
    int descontinuidades = 0;

    for (int i = 0; i < N; ++i) {
        if (visitados[i] == 0) {
            total_arestas += BFS(grafo, i, visitados) - 1;
            ++descontinuidades;
        }
    }
    return descontinuidades*B + total_arestas*E;
}



int main() {
    int T;
    long long int N, M, X, Y, B, E, custo_total;
    cin >> T;

    while(T--){
        cin >> N >> M >> B >> E;
        if (B <= E) {
            cout << B*N << endl;
            //ignore next M inputs
            for (int m = 0; m < M; m++){
                cin >> X >> Y;
            }
        }else{
            vector<Vertice> grafo(N); // Instancia o grafo

            for (int m = 0; m < M; m++){ // le TODAS AS ESTRADAS QUE POSSUEM LIGACOES
                cin >> X >> Y;
                X--;
                Y--;
                grafo[X].adjacencias.emplace(Y); // adiciona aresta
                grafo[Y].adjacencias.emplace(X); // adiciona aresta
            }
            
            custo_total = BFS_grafo_desconexo(grafo, B, E);
            cout << custo_total << endl;
        }
    }

    return 0;
}