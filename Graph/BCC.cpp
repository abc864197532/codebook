const int N = 100000;

vector <int> adj[N], newadj[N];
bool vis[N];
int low[N], dep[N], bcc[N], p[N], _id = 0;
stack <int> stk;

void dfs(int v, int pa) {
    p[v] = pa;
    vis[v] = true;
    stk.push(v);
    low[v] = dep[v] = ~pa ? dep[pa] + 1 : 0;
    for (int u : adj[v]) if (u != pa) {
        if (vis[u]) {
            low[v] = min(low[v], low[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
        }
    }
    if (low[v] == dep[v]) {
        // bridge
        int x;
        do {
            x = stk.top(); stk.pop();
            bcc[x] = _id;
        } while (x != v);
        _id++;
    }
}

void build_bcc(int n) {
    dfs(0, -1);
    for (int v = 1; v < n; ++v) if (low[v] == dep[v]) {
        newadj[bcc[v]].push_back(bcc[p[v]]);
        newadj[bcc[p[v]]].push_back(bcc[v]);
    }
}
