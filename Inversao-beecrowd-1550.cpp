#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

#define MAX 10001
#define INF 999999999

using namespace std;


int inverte(int n){
    string str_n = to_string(n);
    reverse(str_n.begin(), str_n.end());
    return stoi(str_n);
}


vector<int> dijkstra(vector<vector<int>> grafo, int s){
    vector<int> dist(MAX, INF);
    vector<int> prev(MAX, -1);
    dist[s] = 0;
    //queue
    queue<int> q;

    q.push(s);
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (int v : grafo[u]){
            if (dist[v] == INF){
                dist[v] = dist[u] + 1;
                prev[v] = u;
                q.push(v);
            }
        }
    }
    return dist;
}


int main(){
    int T, A, B;
    cin >> T;

    while(T--){
        cin >> A >> B;

        vector<vector<int>> grafo(MAX);

        for (int i=0; i < MAX; i++){
            grafo[i].push_back(i+1);
            grafo[i].push_back(inverte(i));
        }
        
        //imprime resultado
        vector<int> dist = dijkstra(grafo, A);
        cout << dist[B] << endl;

    }

}