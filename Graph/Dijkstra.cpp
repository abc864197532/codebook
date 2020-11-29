const int N = 100000;  

vector <pair <int, long long>> adj[N];
long long dis[N];
int path[N];

void build(int s, int n) {
    for (int i = 0; i < n; ++i) path[i] = -1, dis[i] = 1ll << 60;
    priority_queue <pair <long long, int>, vector <pair <long long, int>>, greater <pair <long long, int>>> pq;
    dis[s] = 0;
    pq.push({dis[s], s});
    long long d;
    int v;
    while (pq.size()) {
        tie(d, v) = pq.top(); pq.pop();
        if (dis[v] < d) continue;
        for (auto E : adj[v]) if (dis[E.first] > dis[v] + E.second) {
            dis[E.first] = dis[v] + E.second;
            path[E.first] = v;
            pq.push({dis[E.first], E.first});
        }
    }
}
