vector <int> adj[N], radj[N];

struct SCC {
    // 0-indexed
    vector <int> newadj[N];
    vector <int> dfs_ord, idx;
    vector <bool> vis;
    int n, nscc;
    SCC () = default;
    SCC (int _n) : n(_n), nscc(0) {
        vis.assign(n, false), idx.assign(n, -1);
        for (int i = 0; i < n; ++i) if (!vis[i])
            dfs(i);
        reverse(dfs_ord.begin(), dfs_ord.end());
        for (int i : dfs_ord) if (idx[i] == -1)
            rdfs(i), nscc++;
        for (int i = 0; i < n; ++i) for (int j : adj[i]) if (idx[i] != idx[j]) {
            newadj[idx[i]].pb(idx[j]);
        }
        for (int i = 0; i < nscc; ++i) {
            sort(newadj[i].begin(), newadj[i].end());
            newadj[i].resize(unique(newadj[i].begin(), newadj[i].end()) - newadj[i].begin());
        }
    }
    void dfs(int v) {
        vis[v] = true;
        for (int u : adj[v]) if (!vis[u])
            dfs(u);
        dfs_ord.push_back(v);
    }
    void rdfs(int v) {
        idx[v] = nscc;
        for (int u : radj[v]) if (idx[u] == -1)
            rdfs(u);
    }
};