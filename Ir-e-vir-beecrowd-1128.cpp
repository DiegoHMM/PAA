#include <iostream>
#include <vector>
#include <queue>
 
using namespace std;
 
 
bool BFS(vector<vector<int>>& grafo,int s,int N){
    queue<int> fila;
    vector<int> cor(N);
    int total_visitas = 1;
    
    cor[s] = 1;
    fila.push(s);
    
    while(!fila.empty()){
        int u = fila.front();
        fila.pop();
        
        for (int i=0;i<grafo[u].size();i++){
            int v = grafo[u][i];
            //cout << "V: " << v << endl;
            //cout << "cor " << cor[v] << endl;
            if (cor[v] == 0){ 
                
                cor[v] = 1;
                fila.push(v);
                total_visitas = total_visitas +1;
                //cout << "Visitando " << v << endl;
                //cout << fila.size() << endl;
            }
        }
        cor[u] = 2;
    }

    return total_visitas == N;
}

int main() {
    int N,M,V,W,P;
    while (true) {
        cin >> N >> M;
        if (N == 0 && M == 0) {
            break;
        }
        vector<vector<int>> grafo(N);
        
        for (int i=0; i<M; i++){ 
            cin >> V >> W >> P;
            V--;
            W--;

            grafo[V].push_back(W);
            if (P==2){
                grafo[W].push_back(V);
            }
        }
        
        int idx = 0;
        while (BFS(grafo, idx, N) && idx < N - 1) {
            idx++;
            //cout << "N " << N-1 << endl;
            //cout <<"idx: " <<idx << endl;
        }
            
        //cout << "idx: " << idx << endl;
        cout << (idx == N - 1 ? "1" : "0") << endl;
    }
    return 0;  
}