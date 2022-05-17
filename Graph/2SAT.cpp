struct TwoSAT {
    // 0-indexed
    // idx i * 2 -> +i, i * 2 + 1 -> -i
    vector <int> adj[N], radj[N], newadj[N];
    vector <int> dfs_ord, idx, solution;
    vector <bool> vis;
    int n, nscc;
    TwoSAT (int _n) : n(_n), nscc(0) {
        idx.assign(n * 2, -1), vis.assign(n * 2, false), solution.assign(n, -1);
    }
    void add_clause(int x, int y) {
        // idx i * 2 -> +i, i * 2 + 1 -> -i
        int nx = x ^ 1, ny = y ^ 1;
        adj[nx].push_back(y), radj[y].push_back(nx);
        adj[ny].push_back(x), radj[x].push_back(ny);
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
    bool find_sol() {
        vis.assign(n, false), idx.assign(n, -1);
        for (int i = 0; i < n * 2; ++i) if (!vis[i])
            dfs(i);
        reverse(dfs_ord.begin(), dfs_ord.end());
        for (int i : dfs_ord) if (idx[i] == -1)
            rdfs(i), nscc++;
        for (int i = 0; i < n; i++) {
            if (idx[i << 1] == idx[i << 1 | 1])
                return false;
            if (idx[i << 1] < idx[i << 1 | 1])
                solution[i] = 0;
            else
                solution[i] = 1;
        }
        return true;
    }
};