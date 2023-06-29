struct LineTree {
    // max
    struct edge {
        int u, v, w;
        bool operator < (const edge &e) {
            return w < e.w;
        }
    };
    struct Dsu {
        vector <vector <int>> cc, weight;
        vector <int> rt;
        Dsu (int n) {
            for (int i = 0; i < n; ++i) {
                cc.pb({i}), weight.pb({}), rt.pb(i);
            }
        }
        void Union(int u, int v, int w) {
            assert(rt[u] != rt[v]);
            u = rt[u], v = rt[v];
            if (cc[u].size() > cc[v].size()) {
                swap(u, v);
            }
            weight[v].pb(w);
            for (int i : cc[u]) {
                cc[v].pb(i), rt[i] = v;
            }
            for (int w : weight[u]) {
                weight[v].pb(w);
            }
            cc[u].clear(), weight[u].clear();
        }
    };
    int n;
    vector <edge> E;
    vector <int> order, weight; // weight[i] = weight(order[i], order[i + 1])
    LineTree (int _n) : n(_n) {}
    void add_edge (int u, int v, int w) {
        E.pb({u, v, w});
    }
    void build() {
        Dsu dsu(n);
        sort(all(E));
        for (auto e : E) {
            dsu.Union(e.u, e.v, e.w);
        }
        order = dsu.cc[dsu.rt[0]], weight = dsu.weight[dsu.rt[0]];
    }
};