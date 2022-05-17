vector <int> adj[N];

struct CentroidDecomposition {
    // 0-index
    vector <int> sz, cd_pa;
    int n;
    CentroidDecomposition(int _n) : n(_n) {
        sz.assign(n, 0), cd_pa.assign(n, -2);
        dfs_cd(0, -1);
    }
    void dfs_sz(int v, int pa) {
        sz[v] = 1;
        for (int u : adj[v]) if (u != pa && cd_pa[u] == -2)
            dfs_sz(u, v), sz[v] += sz[u];
    }
    int dfs_cen(int v, int pa, int s) {
        for (int u : adj[v]) if (u != pa && cd_pa[u] == -2) {
            if (sz[u] * 2 > s)
                return dfs_cen(u, v, s);
        }
        return v;
    }
    vector <int> block;
    void dfs_cd(int v, int pa) {
        dfs_sz(v, pa);
        int c = dfs_cen(v, pa, sz[v]);
        // centroid D&C
        for (int u : adj[c]) if (cd_pa[u] == -2) {
            dfs_ans(u, c);
            // do something
        }
        for (int u : adj[c]) if (cd_pa[u] == -2) {
            dfs_cd(u, c);
        }
    }
    void dfs_ans(int v, int pa) {
        // calculate path through centroid
        // do something
        // remember delete path from the same size
        for (int u : adj[v]) if (u != pa && cd_pa[u] == -2)
            dfs_ans(u, v);
    }
    // Centroid Tree Property:
    // let k = lca(u, v) in Centroid Tree, then dis(u, v) = dis(u, k) + dis(k, v)
};