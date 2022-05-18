template <typename T>
struct Seg {
    // range add value, range query sum
    // 0-indexed, [l, r)
    int l, r, m;
    T val, lz;
    Seg *ch[2];
    Seg () = default;
    Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1), val(0), lz(0) {
        if (r - l > 1) {
            ch[0] = new Seg(l, m);
            ch[1] = new Seg(m, r);
        }
    }
    void pull() {
        val = ch[0]->val + ch[1]->val;
    }
    void give(T x) {
        lz += x, val += x * (r - l);
    }
    void push() {
        ch[0]->give(lz), ch[1]->give(lz), lz = 0;
    }
    void add(int a, int b, int v) {
        if (a <= l && r <= b) {
            give(v);
        } else {
            push();
            if (a < m)
                ch[0]->add(a, b, v);
            if (m < b)
                ch[1]->add(a, b, v);
            pull();
        }
    }
    T query(int a, int b) {
        if (a <= l && r <= b)
            return val;
        push();
        T ans = 0;
        if (a < m)
            ans += ch[0]->query(a, b);
        if (m < b)
            ans += ch[1]->query(a, b);
        return ans;
    }
};