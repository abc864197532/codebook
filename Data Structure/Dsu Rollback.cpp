const int N = 100000;  

struct Dsu {
    struct op {
        int x, dx, y, szy;
    };
    int dsu[N], size[N], n, cc;
    stack <op> stk;
    stack <int> point;
    Dsu (int _n): n(_n), cc(_n) {
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
        stk.push({x, dsu[x], y, size[y]});
        dsu[x] = y;
        size[y] += size[x];
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
        int x = point.top();
        while (stk.size() > x) {
            op A = stk.top(); stk.pop();
            dsu[A.x] = A.dx;
            size[A.y] = A.szy;
            cc++;
        }
        point.pop();
    }
};
