vector <int> adj[N], newadj[N * 2];
bool vis[N], cut[N];
vector <int> bcc[N];
int low[N], dep[N], p[N], _id = 0;
stack <int> stk;

void dfs(int v, int pa) {
    p[v] = pa;
    stk.push(v);
    vis[v] = true;
    low[v] = dep[v] = ~pa ? dep[pa] + 1 : 0;
    int child = 0;
    for (int u : adj[v]) if (u != pa) {
        if (vis[u]) {
            low[v] = min(low[v], dep[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            child++;
            low[v] = min(low[v], low[u]);
            if (low[u] >= dep[v]) {
                // v is a cut point
                cut[v] = true;
                int x;
                do {
                    x = stk.top(); stk.pop();
                    bcc[x].push_back(_id);
                } while (x != u);
                _id++;
            }
        }
    }
    if (!~pa && child < 2) cut[v] = false;
}

void build(int n) {
    for (int i = 0; i < n; ++i) {
        vis[i] = false;
        cut[i] = false;
        bcc[i].clear();
    }
    _id = 0;
    // id <  N means bcc
    // id >= N means cut point
    dfs(0, -1);
    for (int v = 0; v < n; ++v) if (cut[v]) {
            for (int u : bcc[v]) {
                newadj[v + N].push_back(u);
                newadj[u].push_back(v + N);
            }
        }
}
