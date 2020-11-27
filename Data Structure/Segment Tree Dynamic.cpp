struct Seg {
    int l, r, m;
    long long val, lz;
    Seg* ch[2];
    Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1) {
        val = lz = 0;
        ch[0] = ch[1] = NULL;
    }
    // remember to change the pull function!
    void pull() {val = (ch[0] ? ch[0]->val : 0) + (ch[1] ? ch[1]->val : 0);}
    void push() {
        if (r - l > 1 && lz) {
            if (!ch[0]) ch[0] = new Seg(l, m);
            ch[0]->lz += lz;
            ch[0]->val += lz * (m - l);
            if (!ch[1]) ch[1] = new Seg(m, r);
            ch[1]->lz += lz;
            ch[1]->val += lz * (r - m);
        }
        lz = 0;
    }
    void add(int a, int b, long long v) {
        if (a <= l && r <= b) val += v * (r - l), lz += v;
        else {
            push();
            if (a < m) {
                if (!ch[0]) ch[0] = new Seg(l, m);
                ch[0]->add(a, b, v);
            }
            if (m < b) {
                if (!ch[1]) ch[1] = new Seg(m, r);
                ch[1]->add(a, b, v);
            }
            pull();
        }
    }
    long long query(int a, int b) {
        if (a <= l && r <= b) return val;
        push();
        long long ans = 0;
        if (a < m && ch[0]) ans += ch[0]->query(a, b);
        if (m < b && ch[1]) ans += ch[1]->query(a, b);
        return ans;
    }
};
