const int N = 100000, logN = 18;  

vector <int> adj[N];
int jump[N][logN], in[N], out[N], dep[N], _t;

void dfs(int v, int pa) {
    jump[v][0] = pa;
    in[v]= _t++;
    dep[v] = ~pa ? dep[pa] + 1 : 0;
    for (int u : adj[v]) if (u != pa) {
        dfs(u, v);
    }
    out[v] = _t++;
}

void build(int n) {
    for (int i = 0; i < n; ++i) jump[i][0] = -1;
    _t = 0;
    dfs(0, -1);
    for (int j = 1; j < logN; ++j) {
        for (int i = 0; i < n; ++i) {
            int k = jump[i][j - 1];
            if (~k) jump[i][j] = jump[k][j - 1];
        }
    }
}

int lca(int u, int v) {
    if (in[u] <= in[v] && out[u] >= out[v]) return u;
    if (in[v] <= in[u] && out[v] >= out[u]) return v;
    for (int i = logN - 1; i >= 0; --i) {
        int k = jump[u][i];
        if (~k && !(in[k] <= in[v] && out[k] >= out[v])) {
            u = k;
        }
    }
    return jump[u][0];
}

int dis(int u, int v) {
    return dep[u] + dep[v] - dep[lca(u, v)] * 2;
}
