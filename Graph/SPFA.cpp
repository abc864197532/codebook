vector <pair <int, long long>> adj[N];

template <typename T>
struct SPFA {
    vector <T> dis;
    vector <int> rt;
    vector <bool> vis;
    int n, s; T INF;
    SPFA () = default;
    SPFA (int _n, int _s) : n(_n), s(_s), INF(numeric_limits<T>::max()) {
        dis.assign(n, INF), rt.assign(n, -1), vis.assign(n, false);
        queue <int> q;
        dis[s] = 0, q.push(s), vis[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            vis[v] = false;
            for (auto [u, w] : adj[v]) if (dis[u] > dis[v] + w) {
                dis[u] = dis[v] + w, rt[u] = v;
                if (!vis[u])
                    vis[u] = true, q.push(u);
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