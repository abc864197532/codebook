struct MCMF {
    const int INF = 1 << 30;
    struct edge {
        int v, f, c;
        edge (int _v, int _f, int _c) : v(_v), f(_f), c(_c) {}
    };
    vector <edge> E;
    vector <vector <int>> adj;
    vector <int> dis, rt;
    int n, s, t;
    MCMF (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        adj.resize(n);
    }
    void add_edge(int u, int v, int f, int c) {
        adj[u].pb(E.size()), E.pb(edge(v, f, c));
        adj[v].pb(E.size()), E.pb(edge(u, 0, -c));
    }
    bool SPFA() {
        rt.assign(n, -1), dis.assign(n, INF);
        vector <bool> vis(n, false);
        queue <int> q;
        q.push(s), dis[s] = 0, vis[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            vis[v] = false;
            for (int id : adj[v]) if (E[id].f > 0 && dis[E[id].v] > dis[v] + E[id].c) {
                dis[E[id].v] = dis[v] + E[id].c, rt[E[id].v] = id;
                if (!vis[E[id].v]) vis[E[id].v] = true, q.push(E[id].v);
            }
        }
        return dis[t] != INF;
    }
    pair <int, int> runFlow() {
        int cost = 0, flow = 0;
        while (SPFA()) {
            int now = t, add = INF;
            while (now != s) {
                add = min(add, E[rt[now]].f);
                now = E[rt[now] ^ 1].v;
            }
            now = t;
            while (now != s) {
                E[rt[now]].f -= add, E[rt[now] ^ 1].f += add;
                now = E[rt[now] ^ 1].v;
            }
            flow += add, cost += add * dis[t];
        }
        return make_pair(flow, cost);
    }
};