struct LinearBasis {
    vector <int> val;
    int B;
    LinearBasis(int _B) : B(_B) {val.assign(B, 0);}
    void add(int x) {
        for (int i = B - 1; ~i; --i) if (x >> i & 1) {
            if (!val[i]) {
                val[i] = x;
                return;
            }
            x ^= val[i];
        }
    }
    int query(int x) {
        for (int i = B - 1; ~i; --i) if (x >> i & 1) {
            if (val[i])
                x ^= val[i];
        }
        return x;
    }
};