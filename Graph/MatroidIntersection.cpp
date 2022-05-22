struct edge {
    int u, v, c;
};

/* Matroid Condition:
S' \subsetin S \in I, S' \in I
S1, S2 \in I, |S1| < |S2|, then exist e \in S2 \ S1 such that S1 U {e} \in I */
struct GraphMatroid {
    vector <edge> E;
    vector <vector <int>> adj;
    vector <int> comp;
    int n, m;
    GraphMatroid (int _n, vector <edge> _E) : n(_n), E(_E), m(E.size()) {}
    void dfs(int v, int pa, int id) {
        comp[v] = id;
        for (int u : adj[v]) if (u != pa)
            dfs(u, v, id);
    }
    vector <bool> build_X(vector <bool> &I) {
        adj.assign(n, vector <int>());
        for (int i = 0; i < m; ++i) if (I[i]) {
            adj[E[i].u].push_back(E[i].v);
            adj[E[i].v].push_back(E[i].u);
        }
        comp.assign(n, -1);
        int id = 0;
        for (int i = 0; i < n; ++i) if (comp[i] == -1)
            dfs(i, -1, id), id++;
        vector <bool> X(m, false);
        for (int i = 0; i < m; ++i) if (!I[i] && comp[E[i].u] != comp[E[i].v])
            X[i] = true;
        return X;
    }
    void build_exchange_graph(vector <vector <int>> &adj, vector <bool> &I) {
        for (int i = 0; i < m; ++i) if (I[i]) {
            adj.assign(n, vector <int>());
            for (int j = 0; j < m; ++i) if (I[j] && i != j) {
                adj[E[j].u].push_back(E[j].v);
                adj[E[j].v].push_back(E[j].u);
            }
            comp.assign(n, -1);
            int id = 0;
            for (int j = 0; j < n; ++j) if (comp[j] == -1)
                dfs(j, -1, id), id++;
            for (int j = 0; j < m; ++j) if (!I[j] && comp[E[j].u] != comp[E[j].v]) {
                adj[i].push_back(j);
            }
        }
    }
};

struct ColorMatroid {
    vector <edge> E;
    int n;
    ColorMatroid (vector <edge> _E) : E(_E), n(E.size()) {}
    vector <bool> build_X(vector <bool> &I) {
        vector <bool> vis(n, false);
        for (int i = 0; i < n; ++i) if (I[i])
            vis[E[i].c] = true;
        vector <bool> X(n, false);
        for (int i = 0; i < n; ++i) if (!I[i] && !vis[E[i].c])
            X[i] = true;
        return X;
    }
    void build_exchange_graph(vector <vector <int>> &adj, vector <bool> &I) {
        vector <bool> vis(n, false);
        for (int i = 0; i < n; ++i) if (I[i])
            vis[E[i].c] = true;
        for (int i = 0; i < n; ++i) if (I[i]) {
            vis[E[i].c] = false;
            for (int j = 0; j < n; ++j) if (!I[j] && !vis[E[j].c]) {
                adj[j].push_back(i);
            }
            vis[E[i].c] = true;
        }
    }
};

template <typename M1, typename M2>
struct MatroidIntersection {
    M1 m1;
    M2 m2;
    MatroidIntersection (M1 _m1, M2 _m2) : m1(_m1), m2(_m2) {}
    /* 1. build X1, X2
       2. If e \in X1 and e \in X2, add e
       3. Else build exchange graph
          m1 -> add edge from I to E \ I
          m2 -> add edge from E \ I to I
          weight: I -> w, E \ I -> -w
       4. find a minimum path (weight, number) from X1 to X2 (use bfs or SPFA) */
    vector <vector <int>> adj;
    vector <int> bfs(vector <bool> &X1, vector <bool> &X2) {
        int n = X1.size();
        queue <int> q;
        vector <int> dis(n, -1), rt(n, -1);
        for (int i = 0; i < n; ++i) if (X1[i])
            q.push(i), dis[i] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : adj[v]) if (dis[u] == -1) {
                dis[u] = dis[v] + 1, rt[u] = v;
                q.push(u);
            }
        }
        pair <int, int> mn = make_pair(1 << 30, -1);
        for (int i = 0; i < n; ++i) if (X2[i] && dis[i] != -1)
            mn = min(mn, make_pair(dis[i], i));
        int now = mn.second;
        if (now == -1)
            return {};
        vector <int> path = {now};
        while (rt[now] != -1) {
            now = rt[now], path.push_back(now);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    vector <bool> solve(int n) {
        vector <bool> I(n, false);
        while (true) {
            vector <bool> X1 = m1.build_X(I), X2 = m2.build_X(I);
            if (count(X1.begin(), X1.end(), 0) == n || count(X2.begin(), X2.end(), 0) == n)
                break;
            int add = -1;
            for (int i = 0; i < n; ++i) if (X1[i] && X2[i]) {
                add = i;
                break;
            }
            if (add != -1) {
                I[add] = true;
                continue;
            }
            adj.assign(n, vector <int>());
            m1.build_exchange_graph(adj, I);
            m2.build_exchange_graph(adj, I);
            vector <int> path = bfs(X1, X2);
            if (path.empty())
                break;
            for (int i : path)
                I[i] = !I[i];
        }
        return I;
    }
    vector <int> SPFA(vector <bool> &X1, vector <bool> &X2, vector <bool> &I, vector <int> &weight) {
        int n = X1.size();
        queue <int> q;
        vector <pair <int, int>> dis(n, make_pair(1 << 30, -1));
        vector <int> rt(n, -1);
        vector <bool> vis(n, false);
        for (int i = 0; i < n; ++i) if (X1[i])
            q.push(i), dis[i] = make_pair(-weight[i], 0), vis[i] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            vis[v] = false;
            for (int u : adj[v]) {
                pair <int, int> nxt = mp(dis[v].first + (I[u] ? weight[u] : -weight[u]), dis[v].second + 1);
                if (dis[u] > nxt) {
                    dis[u] = nxt, rt[u] = v;
                    if (!vis[u])
                        q.push(u), vis[u] = true;
                }
            }
        }
        pair <pair <int, int>, int> mn = make_pair(make_pair(1 << 30, -1), -1);
        for (int i = 0; i < n; ++i) if (X2[i])
            mn = min(mn, make_pair(dis[i], i));
        int now = mn.second;
        if (now == -1)
            return {};
        vector <int> path = {now};
        while (rt[now] != -1) {
            now = rt[now], path.push_back(now);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    vector <bool> solve_max_weight(vector <int> weight) {
        int n = weight.size();
        vector <bool> I(n, false);
        while (true) {
            vector <bool> X1 = m1.build_X(I), X2 = m2.build_X(I);
            if (count(X1.begin(), X1.end(), 0) == n || count(X2.begin(), X2.end(), 0) == n)
                break;
            adj.assign(n, vector <int>());
            m1.build_exchange_graph(adj, I);
            m2.build_exchange_graph(adj, I);
            vector <int> path = SPFA(X1, X2, I, weight);
            if (path.empty())
                break;
            for (int i : path)
                I[i] = !I[i];
        }
        return I;
    }
};