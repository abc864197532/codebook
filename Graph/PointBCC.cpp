vector <int> adj[N], newadj[N << 1], bcc[N];
pii E[M];
bool vis[N], vis2[M], cut[N];
vector <int> stk;
int low[N], dep[N], nbcc;

void dfs(int v, int pa, int w = -1) {
    if (~w) stk.pb(w), vis2[w] = true;
    low[v] = dep[v] = ~pa ? dep[pa] + 1 : 0;
    vis[v] = true;
    for (int id : adj[v]) {
        int u = E[id].first ^ E[id].second ^ v, ch = 0;
        if (vis[u]) {
            if (!vis2[id]) stk.pb(id), vis2[id] = true;
            low[v] = min(low[v], dep[u]);
        } else {
            dfs(u, v, id);
            ch++;
            low[v] = min(low[v], low[u]);
            if (low[u] >= dep[v]) {
                cut[v] = true;
                int x;
                do {
                    x = stk.back(); stk.pop_back();
                    bcc[nbcc].push_back(x);
                } while (x != id);
                nbcc++;
            }
        }
        if (pa == -1 && ch < 2) 
            cut[v] = false;
    }
}

void build() {
    fill(vis, vis + N, false), fill(vis2, vis2 + M, false);
    fill(cut, cut + N, false), nbcc = 0;
    dfs(0, -1);
    for (int i = 0; i < nbcc; ++i) {
        vector <int> V;
        for (int id : bcc[i]) {
            V.pb(E[id].first);
            V.pb(E[id].second);
        }
        sort(all(V)), V.resize(unique(all(V)) - V.begin());
        // id  < N -> vertex
        // id >= N -> bcc
        for (int v : V) {
            newadj[i + N].push_back(v);
            newadj[v].push_back(i + N);
        }
    }
}