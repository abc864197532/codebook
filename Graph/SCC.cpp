const int N = 100000;

vector <int> adj[N], radj[N];
int scc[N], _id = 0;
bool vis[N];
vector <int> order;

void rdfs(int v) {
    vis[v] = true;
    for (int u : radj[v]) if (!vis[u]) {
        rdfs(u);
    }
    order.push_back(v);
}

void dfs(int v) {
    scc[v] = _id;
    for (int u : adj[v]) if (scc[u] == -1) {
        dfs(u);
    }
}

void build(int n) {
    _id = 0;
    order.clear();
    for (int i = 0; i < n; ++i) {
        vis[i] = false;
        scc[i] = -1;
    }
    for (int i = 0; i < n; ++i) if (!vis[i]) {
        rdfs(i);
    }
    reverse(order.begin(), order.end());
    for (int v : order) {
        if (scc[v] == -1) {
            dfs(v);
            _id++;
        }
    }
}
