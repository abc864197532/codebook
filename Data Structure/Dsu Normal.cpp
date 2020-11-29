const int N = 100000;  

struct Dsu {
    int dsu[N], size[N], n, cc;
    Dsu (int _n) : n(_n), cc(_n) {
        for (int i = 0; i < n; ++i) {
            dsu[i] = i;
            size[i] = 1;
        }
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
