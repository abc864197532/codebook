struct Dsu {
    struct op {
        int x, dx, y, szy;
    };
    int n, cc;
    vector <int> dsu, size;
    vector <op> stk;
    vector <int> point;
    Dsu (int _n): n(_n) {
        dsu.resize(n);
        size.resize(n);
        cc = n;
        for (int i = 0; i < n; ++i) {
            dsu[i] = i;
            size[i] = 1;
        }
    }
    int Find(int a) {
        if (dsu[a] == a) return a;
        return Find(dsu[a]);
    }
    bool Union(int a, int b) {
        int x = Find(a), y = Find(b);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        stk.push_back({x, dsu[x], y, size[y]});
        dsu[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }
    bool same(int u, int v) {
        return Find(u) == Find(v);
    }
    void addPoint() {
        point.push_back(stk.size());
    }
    void rollback() {
        while (stk.size() > point.back()) {
            op A = stk.back(); stk.pop_back();
            dsu[A.x] = A.dx;
            size[A.y] = A.szy;
            cc++;
        }
        point.pop_back();
    }
};
