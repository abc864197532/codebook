struct Dsu {
    struct op {
        int x, dx, y, szy;
    };
    vector <int> rt, sz;
    stack <op> stk;
    stack <int> point;
    int n, cc;
    Dsu () = default;
    Dsu (int _n) : n(_n), cc(_n) {
        rt.resize(n), iota(rt.begin(), rt.end(), 0);
        sz.assign(n, 1);
    }
    int Find(int v) {
        return rt[v] == v ? v : Find(rt[v]);
    }
    bool Union(int v, int u) {
        u = Find(u), v = Find(v);
        if (u == v) {
            return false;
        }
        if (sz[u] > sz[v]) {
            swap(u, v);
        }
        stk.push({u, rt[u], v, sz[v]});
        rt[u] = v;
        sz[v] += sz[u];
        cc--;
        return true;
    }
    bool same(int u, int v) {
        return Find(u) == Find(v);
    }
    void addPoint() {
        point.push(stk.size());
    }
    void rollback() {
        while (stk.size() > point.top()) {
            op A = stk.top(); stk.pop();
            rt[A.x] = A.dx;
            sz[A.y] = A.szy;
            cc++;
        }
        point.pop();
    }
};