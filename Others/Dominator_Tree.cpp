vector <int> adj[N], radj[N];
 
struct dominator_tree {
    int vis[N], revis[N], sdom[N], idom[N], par[N], n, id, rt[N], mn[N];
    vector <int> bucket[N], newadj[N];
    /* sdom[w] = for all (v, w) \in E
     *           if v < w : v
     *           else : sdom(u), u = anc(v)
     * idom[w] = for u from sdom[w] to w, let x = min(sdom[u])
     *           if sdom[u] == sdom[w] : sdom[w]
     *           else : idom[u]
     * add edge idom[u] -> u
     */
    int query(int u, int x = 0) {
        if (rt[u] == u) return x ? -1 : u;
        int v = query(rt[u], x + 1);
        if (v < 0) return u;
        if (vis[sdom[mn[u]]] > vis[sdom[mn[rt[u]]]]) mn[u] = mn[rt[u]];
        rt[u] = v;
        return x ? v : mn[u];
    }
    dominator_tree(int _n) : n(_n), id(0) {
        for (int i = 0; i < n; ++i) rt[i] = i, vis[i] = -1;
    }
    void dfs(int v) {
        vis[v] = id, revis[id] = v, id++;
        idom[v] = sdom[v] = mn[v] = v;
        for (int u : adj[v]) if (vis[u] == -1) {
            par[u] = v;
            dfs(u);
        }
    }
    void build(int s) {
        dfs(s);
        for (int i = id - 1; ~i; --i) {
            int v = revis[i];
            for (int u : radj[v]) {
                int x = query(u);
                if (vis[sdom[v]] > vis[sdom[x]]) sdom[v] = sdom[x];
            }
            if (i) bucket[sdom[v]].pb(v);
            for (int u : bucket[v]) {
                int x = query(u);
                if (sdom[u] == sdom[x]) idom[u] = sdom[u];
                else idom[u] = x;
            }
            if (i) rt[v] = par[v];
        }
        for (int i = 1; i < id; ++i) {
            int v = revis[i];
            if (idom[v] != sdom[v]) idom[v] = idom[idom[v]];
            newadj[idom[v]].pb(v);
            newadj[v].pb(idom[v]);
        }
    }
};
