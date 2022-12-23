vector <int> adj[N], newadj[N];
int low[N], dep[N], idx[N], par[N], nbcc;
bool bridge[N];
vector <int> stk;

void dfs(int v, int pa) {
    low[v] = dep[v] = ~pa ? dep[pa] + 1 : 0;
    par[v] = pa;
    stk.push_back(v);
    for (int u : adj[v]) if (u != pa) {
        if (dep[u] == -1) {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
        } else {
            low[v] = min(low[v], low[u]);
        }
    }
    if (low[v] == dep[v]) {
        bridge[v] = true;
        int x;
        do {
            x = stk.back(), stk.pop_back();
            idx[x] = nbcc;
        } while (x != v);
        nbcc++;
    }
}

void build() {
    fill(dep, dep + N, -1), fill(bridge, bridge + N, false);
    nbcc = 0;
    dfs(0, -1);
    for (int i = 1; i < N; ++i) if (bridge[i]) {
        newadj[idx[i]].pb(idx[par[i]]);
        newadj[idx[par[i]]].pb(idx[i]);
    }
}
