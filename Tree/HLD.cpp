vector <int> adj[N];

struct HLD {
    // 0-index
    vector <int> dep, pt, hd, idx, sz, par, vis;
    int n, _t;
    HLD () = default;
    HLD (int _n) : n(_n) {
        pt.assign(n, -1), hd.assign(n, -1), par.assign(n, -1);
        idx.assign(n, 0), sz.assign(n, 0), dep.assign(n, 0), vis.assign(n, 0);
        _t = 0;
        for (int i = 0; i < n; ++i) if (!vis[i]) {
            dfs1(i, -1);
            dfs2(i, -1, 0);
        }
    }
    void dfs1(int v, int pa) {
        par[v] = pa;
        dep[v] = ~pa ? dep[pa] + 1 : 0;
        sz[v] = vis[v] = 1;
        for (int u : adj[v]) if (u != pa) {
            dfs1(u, v);
            if (pt[v] == -1 || sz[pt[v]] < sz[u])
                pt[v] = u;
            sz[v] += sz[u];
        }
    }
    void dfs2(int v, int pa, int h) {
        if (v == -1)
            return;
        idx[v] = _t++, hd[v] = h;
        dfs2(pt[v], v, h);
        for (int u : adj[v]) if (u != pa && u != pt[v]) {
            dfs2(u, v, u);
        }
    }
    void modify(int u, int v) {
        while (hd[u] != hd[v]) {
            if (dep[hd[u]] < dep[hd[v]])
                swap(u, v);
            // range [idx[hd[u]], idx[u] + 1)
            u = par[hd[u]];
        }
        if (dep[u] < dep[v])
            swap(u, v);
        // range [idx[v], idx[u] + 1)
    }
    int query(int u, int v) {
        int ans = 0;
        while (hd[u] != hd[v]) {
            if (dep[hd[u]] < dep[hd[v]])
                swap(u, v);
            // range [idx[hd[u]], idx[u] + 1)
            u = par[hd[u]];
        }
        if (dep[u] < dep[v])
            swap(u, v);
        // range [idx[v], idx[u] + 1)
        return ans;
    }
};