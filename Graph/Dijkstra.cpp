vector <pair <int, long long>> adj[N];

template <typename T>
struct Dijkstra {
    vector <T> dis;
    vector <int> rt;
    int n, s; T INF;
    Dijkstra () = default;
    Dijkstra (int _n, int _s) : n(_n), s(_s), INF(numeric_limits<T>::max()) {
        dis.assign(n, INF), rt.assign(n, -1);
        priority_queue <pair <T, int>, vector <pair <T, int>>, greater <pair <T, int>>> pq;
        dis[s] = 0, pq.emplace(dis[s], s);
        while (!pq.empty()) {
            T f; int v; tie(f, v) = pq.top(); pq.pop();
            if (dis[v] < f)
                continue;
            for (auto [u, w] : adj[v]) if (dis[u] > dis[v] + w) {
                dis[u] = dis[v] + w, rt[u] = v;
                pq.emplace(dis[u], u);
            }
        }
    }
    vector <int> get_path(int t) {
        vector <int> path;
        while (t != s) {
            path.push_back(t), t = rt[t];
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        return path;
    }
};