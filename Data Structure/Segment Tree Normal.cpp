struct Seg {  
    int l, r, m;
    long long val, lz;
    Seg* ch[2];
    Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1) {
        if (r - l > 1) {
            ch[0] = new Seg(l, m);
            ch[1] = new Seg(m, r);
            pull();
        }
        val = lz = 0;
    }
    void pull() {val = ch[0]->val + ch[1]->val;}
    void push() {
        if (r - l > 1 && lz) {
            ch[0]->lz += lz;
            ch[0]->val += lz * (m - l);
            ch[1]->lz += lz;
            ch[1]->val += lz * (r - m);
        }
        lz = 0;
    }
    void add(int a, int b, long long v) {
        if (a <= l && r <= b) val += v * (r - l), lz += v;
        else {
            push();
            if (a < m) ch[0]->add(a, b, v);
            if (m < b) ch[1]->add(a, b, v);
            pull();
        }
    }
    long long query(int a, int b) {
        if (a <= l && r <= b) return val;
        push();
        long long ans = 0;
        if (a < m) ans += ch[0]->query(a, b);
        if (m < b) ans += ch[1]->query(a, b);
        return ans;
    }
};
