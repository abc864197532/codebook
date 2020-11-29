const int N = 100000;

vector <int> adj[N];
int pt[N], sz[N], id[N], hd[N], par[N], dep[N], _t;

void dfs(int v = 0, int pa = -1) {
    sz[v] = 1;
    par[v] = pa;
    pt[v] = -1;
    dep[v] = ~pa ? dep[pa] + 1 : 0;
    for (int u : adj[v]) if (u != pa) {
            dfs(u, v);
            sz[v] += sz[u];
            if (pt[v] == -1 || sz[pt[v]] < sz[u]) pt[v] = u;
        }
}

void hld(int v, int pa, int h) {
    if (!~v) return;
    id[v] = _t++;
    hd[v] = h;
    hld(pt[v], v, h);
    for (int u : adj[v]) if (u != pa && u != pt[v]) {
        hld(u, v, u);
    }
}

void build() {
    _t = 0;
    dfs(0, -1);
    hld(0, -1, 0);
}

int query (int u, int v, int x) {
    while (hd[u] != hd[v]) {
        if (dep[hd[u]] < dep[hd[v]]) swap(u, v);
        // from id[hd[u]] to id[u] + 1
        u = par[hd[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    // from id[u] to id[v] + 1
}
