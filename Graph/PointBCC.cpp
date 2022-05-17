vector <int> adj[N];

struct PointBCC {
    vector <int> newadj[N << 1];
    vector <vector <int>> idx;
    vector <int> low, dep, par, stk;
    vector <bool> cut;
    int n, nbcc;
    PointBCC (int _n) : n(_n), nbcc(0) {
        low.assign(n, -1), dep.assign(n, -1), idx.assign(n, vector <int> ());
        par.assign(n, -1), cut.assign(n, false);
        for (int i = 0; i < n; ++i) if (dep[i] == -1)
            dfs(i, -1);
        // idx  < n -> bcc
        // idx >= n -> cut point
        for (int i = 0; i < n; ++i) if (cut[i]) {
            for (int j : idx[i]) {
                newadj[j].push_back(i + n);
                newadj[i + n].push_back(j);
            }
        }
    }
    void dfs(int v, int pa) {
        low[v] = dep[v] = ~pa ? dep[pa] + 1 : 0;
        stk.push_back(v);
        par[v] = pa;
        int ch = 0;
        for (int u : adj[v]) if (u != pa) {
            if (dep[u] == -1) {
                dfs(u, v);
                low[v] = min(low[v], low[u]);
                ch++;
                if (low[u] >= dep[v]) {
                    // v is a cut point
                    cut[v] = true;
                    int x;
                    do {
                        x = stk.back(), stk.pop_back();
                        idx[x].push_back(nbcc);
                    } while (x != u);
                    idx[v].push_back(nbcc++);
                }
            } else {
                low[v] = min(low[v], dep[u]);
            }
        }
        if (pa == -1 && ch < 2) 
            cut[v] = false;
    }
};