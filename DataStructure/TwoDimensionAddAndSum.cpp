struct TwoDimensionAddAndSum {
    // 0-index, [l, r)
    struct Seg {
        int l, r, m;
        long long vala, valb, lza, lzb;
        Seg* ch[2];
        Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1), vala(0), valb(0), lza(0), lzb(0) {
            if (r - l > 1) {
                ch[0] = new Seg(l, m);
                ch[1] = new Seg(m, r);
            }
        }
        void pull() {vala = ch[0]->vala + ch[1]->vala, valb = ch[0]->valb + ch[1]->valb;}
        void give(long long a, long long b) {
            lza += a, lzb += b;
            vala += a * (r - l), valb += b * (r - l);
        }
        void push() {
            ch[0]->give(lza, lzb), ch[1]->give(lza, lzb), lza = lzb = 0;
        }
        void add(int a, int b, long long va, long long vb) {
            if (a <= l && r <= b)
                give(va, vb);
            else {
                push();
                if (a < m)
                    ch[0]->add(a, b, va, vb);
                if (m < b)
                    ch[1]->add(a, b, va, vb);
                pull();
            }
        }
        long long query(int a, int b, long long v) {
            if (a <= l && r <= b)
                return vala * v + valb;
            push();
            long long ans = 0;
            if (a < m)
                ans += ch[0]->query(a, b, v);
            if (m < b)
                ans += ch[1]->query(a, b, v);
            return ans;
        }
    };
    vector <array <long long, 4>> E[N];
    vector <array <long long, 4>> Q[N];
    vector <long long> ans;
    void add_event(int x1, int y1, int x2, int y2, long long v) {
        E[x1].pb({y1, y2,  v, -v * x1});
        E[x2].pb({y1, y2, -v, v * x2});
    }
    void add_query(int x1, int y1, int x2, int y2, int id) {
        Q[x1].pb({y1, y2, -1, id});
        Q[x2].pb({y1, y2, 1, id});
        ans.pb(0);
    }
    void run(int n) {
        Seg root(0, n);
        for (int i = 0; i <= n; ++i) {
            for (auto j : E[i])
                root.add(j[0], j[1], j[2], j[3]);
            for (auto j : Q[i])
                ans[j[3]] += j[2] * root.query(j[0], j[1], i);
        }
    }
};