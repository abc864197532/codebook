const int N = 100000;

vector <int> adj[N];
int sz[N], cd_pa[N];

void dfs1 (int v, int pa) { // count size
    sz[v] = 1;
    for (int u : adj[v]) if (u != pa and cd_pa[u] == -1) {
        dfs1(u, v);
        sz[v] += sz[u];
    }
}

int dfs2 (int v, int pa, int n) { // find cen
    for (int u : adj[v]) if (u != pa and cd_pa[u] == -1 and sz[u] > n / 2) {
        return dfs2(u, v, n);
    }
    return v;
}

void cd (int v, int pa) { // build cdt
    dfs1(v, pa);
    int c = dfs2(v, pa, sz[v]);
    cd_pa[c] = ~pa ? pa : -2;
    for (int u : adj[c]) if (cd_pa[u] == -1) {
        cd(u, c);
    }
    if (pa == -1) cd_pa[c] = -1;
}

void build(int n) {
    for (int i = 0; i < n; ++i) cd_pa[i] = -1;
    cd(0, -1);
}
