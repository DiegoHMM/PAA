#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long int INF = 9223372036854775807LL;
const int MAX = 101;

long long int capacity[MAX][MAX];
long long int flow[MAX][MAX];
long long int cost[MAX][MAX];
long long int previous[MAX];
long long int friends;
long long int K;
long long int total_cost = 0;

long long int dist[MAX];
bool visited[MAX];

long long int minDistance(long long int dist[], bool visited[], int N) {
    long long int min_dist = INF, min_index = -1;
    for (long long int v = 0; v < N; v++) {
        if (!visited[v] && dist[v] < min_dist) {
            min_dist = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

bool dijkstra(long long int source, long long int sink, long long int N) {
    for (long long int i = 0; i < N; i++) {
        dist[i] = INF;
        visited[i] = false;
        previous[i] = -1;
    }
    dist[source] = 0;

    for (long long int count = 0; count < N - 1; count++) {
        long long int u = minDistance(dist, visited, N);
        visited[u] = true;
        for (long long int v = 0; v < N; v++) {
            if (!visited[v] && capacity[u][v] - flow[u][v] > 0 && cost[u][v] < INF &&
                dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                previous[v] = u;
            }
        }
    }

    if (dist[sink] == INF)
        return false;

    vector<long long int> path;
    long long int u = sink;
    while (u != source) {
        path.push_back(u);
        u = previous[u];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    long long int bottleneck = INF;
    for (long long int i = 0; i < path.size() - 1; i++) {
        long long int u = path[i], v = path[i + 1];
        bottleneck = min(friends, capacity[u][v] - flow[u][v]);
    }
    friends -= K;
    for (long long int i = 0; i < path.size() - 1; i++) {
        long long int u = path[i], v = path[i + 1];
        if (capacity[u][v] - flow[u][v] > 0) {
            flow[u][v] += bottleneck;
            flow[v][u] -= bottleneck;
        }
    }

    return true;
}

void edmonds_karp(long long int source, long long int sink, long long int N) {
    while (dijkstra(source, sink, N)) {
        if (friends <= 0)
            break;
    }

    for (long long int i = 0; i < N; i++) {
        for (long long int j = 0; j < N; j++) {
            if (flow[i][j] > 0) {
                total_cost += flow[i][j] * cost[i][j];
            }
        }
    }
}

int main() {
    long long int instance = 0;
    long long int N, M;
    while (cin >> N >> M) {
        total_cost = 0;
        friends = 0;
        K = 0;
        instance++;
    
        long long int u, v, c;
        queue<long long int> q_inputs;

       
        for (long long int i = 0; i < M; i++) {
            cin >> u >> v >> c;
            u--;
            v--;
            q_inputs.push(u);
            q_inputs.push(v);
            q_inputs.push(c);
        }

        cin >> friends >> K;

        for (long long int i = 0; i < N; i++) {
            for (long long int j = 0; j < N; j++) {
                capacity[i][j] = 0;
                cost[i][j] = INF;
                flow[i][j] = 0;
            }
        }

        // Populate capacity and cost matrices
        for (long long int i = 0; i < M; i++) {
            u = q_inputs.front();
            q_inputs.pop();
            v = q_inputs.front();
            q_inputs.pop();
            c = q_inputs.front();
            q_inputs.pop();
            capacity[u][v] = K;
            capacity[v][u] = K;
            cost[u][v] = c;
            cost[v][u] = c;
        }

        edmonds_karp(0, N - 1, N);
        cout << "Instancia " << instance << endl;
        if (friends > 0) {
            cout << "impossivel" << "\n" << endl;
        } else {
            cout << total_cost << "\n" << endl;
        }
    }
    return 0;
}
