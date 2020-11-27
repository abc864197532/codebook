vector <int> adj[N];
vector <int> pt(N, -1), sz(N, 1), idx(N, -1), hd(N, -1), par(N, -1), depth(N);
int _id = 0;

void dfs(int v = 0, int pa = -1) {
    par[v] = pa;
    depth[v] = ~pa ? depth[pa] + 1 : 0;
    for (int u : adj[v]) if (u != pa) {
            dfs(u, v);
            sz[v] += sz[u];
            if (pt[v] == -1 || sz[pt[v]] < sz[u]) pt[v] = u;
        }
}

void hld(int v = 0, int pa = -1, int h = 0) {
    if (v == -1) return;
    idx[v] = _id++;
    hd[v] = h;
    hld(pt[v], v, h);
    for (int u : adj[v]) if (u != pa && u != pt[v]) {
            hld(u, v, u);
        }
}

void modify(int u, int v, int x) {
    while (hd[u] != hd[v]) {
        if (depth[hd[u]] < depth[hd[v]]) swap(u, v);
        // add from idx[hd[u]] to idx[u] + 1
        u = par[hd[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    // add from u to v + 1
}

int query(int u, int v) {
    int ans = 0;
    while (hd[u] != hd[v]) {
        if (depth[hd[u]] < depth[hd[v]]) swap(u, v);
        // add ans from idx[hd[u]] to idx[u] + 1
        u = par[hd[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    // add ans from u to v + 1
    return ans;
}
