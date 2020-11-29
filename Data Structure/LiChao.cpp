struct Line {
    long long m, k; // y = mx + k
    long long v(long long x) {
        return m * x + k;
    }
};

struct LiChao {
    int l, r, m;
    Line best;
    LiChao* ch[2] = {NULL, NULL};
    LiChao(int _l, int _r) : l(_l), r(_r), m(l + r >> 1) {
        best.m = 0;
        best.k = 1ll << 60;
    }
    void insert(Line seg) {
        if (r - l == 1) {
            if (best.v(l) > seg.v(l)) {
                swap(best, seg);
            }
        } else {
            if (best.m > seg.m) swap(seg, best);
            if (best.v(m) > seg.v(m)) {
                swap(seg, best);
                if (!ch[1]) ch[1] = new LiChao(m, r);
                ch[1]->insert(seg);
            } else {
                if (!ch[0]) ch[0] = new LiChao(l, m);
                ch[0]->insert(seg);
            }
        }
    }
    long long query(long long x) {
        if (r - l == 1) return best.v(x);
        if (x < m && ch[0]) return min(ch[0]->query(x), best.v(x));
        if (x >= m && ch[1]) return min(ch[1]->query(x), best.v(x));
        return best.v(x);
    }
};
