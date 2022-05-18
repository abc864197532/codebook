vector <int> adj[N];

struct BinaryLifting {
    // 0-index
    vector <int> in, out, dep;
    vector <vector <int>> jump;
    int _t, n, lg;
    BinaryLifting () = default;
    BinaryLifting (int _n) : n(_n) {
        lg = __lg(n) + 1, _t = 0;
        jump.assign(n, vector <int> (lg, -1));
        in.assign(n, 0), out.assign(n, 0), dep.assign(n, 0);
        dfs(0, -1);
    }
    void dfs(int v, int pa) {
        in[v] = _t++, jump[v][0] = pa;
        dep[v] = ~pa ? dep[pa] + 1 : 0;
        for (int i = 1; i < lg; ++i) {
            int k = jump[v][i - 1];
            jump[v][i] = ~k ? jump[k][i - 1] : k;
        }
        for (int u : adj[v]) if (u != pa) {
            dfs(u, v);
        }
        out[v] = _t++;
    }
    bool anc(int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    }
    int lca(int u, int v) {
        if (anc(u, v))
            return u;
        if (anc(v, u))
            return v;
        for (int i = lg - 1; ~i; --i) {
            int k = jump[u][i];
            if (~k && !anc(k, v))
                u = k;
        }
        return jump[u][0];
    }
    int lift(int u, int d) {
        for (int i = 0; i < lg; ++i) if (d >> i & 1)
            u = jump[u][i];
        return u;
    }
    int dis(int u, int v) {
        return dep[u] + dep[v] - dep[lca(u, v)] * 2;
    }
};