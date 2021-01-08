struct MCMF {
    const long long INF = 1ll << 60;
    struct edge {
        int v, id, revid;
        long long f, c;
        edge (int _v, long long _f, long long _c, int _id, int _revid) : v(_v), f(_f), c(_c), id(_id), revid(_revid) {}
    };
    vector <vector <edge>> adj;
    vector <pair <int, int>> rt;
    vector <long long> dis;
    int n, s, t;
    MCMF (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        adj.resize(n);
    }
    void add_edge(int u, int v, long long f, long long c) {
        adj[u].push_back(edge(v, f, c, adj[u].size(), adj[v].size()));
        adj[v].push_back(edge(u, 0, -c, adj[v].size(), adj[u].size() - 1));
    }
    bool SPFA() {
        rt.assign(n, make_pair(-1, -1));
        dis.assign(n, INF);
        vector <bool> vis(n, false);
        queue <int> q;
        q.push(s);
        dis[s] = 0;
        vis[s] = true;
        while (q.size()) {
            int v = q.front(); q.pop();
            vis[v] = false;
            for (edge &e : adj[v]) if (e.f > 0 && dis[e.v] > dis[v] + e.c) {
                dis[e.v] = dis[v] + e.c;
                rt[e.v] = make_pair(v, e.id);
                if (!vis[e.v]) {
                    vis[e.v] = true;
                    q.push(e.v);
                }
            }
        }
        return dis[t] != INF;
    }
    pair <long long, long long> runFlow() { // cost, flow
        long long cost = 0, flow = 0;
        while (SPFA()) {
            vector <pair <int, int>> E;
            int v = t;
            long long addflow = INF;
            while (v != s) {
                E.push_back(rt[v]);
                addflow = min(addflow, adj[rt[v].first][rt[v].second].f);
                v = rt[v].first;
            }
            for (pair <int, int> a : E) {
                adj[a.first][a.second].f -= addflow;
                adj[adj[a.first][a.second].v][adj[a.first][a.second].revid].f += addflow;
            }
            flow += addflow;
            cost += addflow * dis[t];
        }
        return make_pair(cost, flow);
    }
};
