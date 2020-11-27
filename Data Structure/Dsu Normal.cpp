struct Dsu {
    int n;
    vector <int> dsu, sz;
    Dsu (int _n) : n(_n) {
        dsu.resize(n);
        sz.assign(n, 1);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int Find(int v) {
        if (dsu[v] == v) return v;
        return dsu[v] = Find(dsu[v]);
    }
    bool Union(int v, int u) {
        int x = Find(v), y = Find(u);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        dsu[x] = y;
        sz[y] += sz[x];
        sz[x] = 0;
        return true;
    }
    bool same(int u, int v) {
        return Find(u) == Find(v);
    }
};
