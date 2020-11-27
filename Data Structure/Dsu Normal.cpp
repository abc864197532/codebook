struct Dsu {
    int n, cc;
    vector <int> dsu, size;
    Dsu (int _n) : n(_n), cc(_n) {
        dsu.assign(n, 0);
        size.assign(n, 1);
        iota(dsu.begin(), dsu.end(), 0);
    }
    int Find(int v) {
        if (dsu[v] == v) return v;
        return dsu[v] = Find(dsu[v]);
    }
    bool Union(int v, int u) {
        int x = Find(v), y = Find(u);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        dsu[x] = y;
        size[y] += size[x];
        size[x] = 0;
        cc--;
        return true;
    }
    bool same(int u, int v) {
        return Find(u) == Find(v);
    }
};
