struct BIT {
    int n;
    vector <long long> bit;
    BIT (int _n) : n(_n) {
        bit.assign(n + 1, 0);
    }
    void add (int p, long long a) {
        for (int i = p; i <= n; i += (i & -i)) bit[i] += a;
    }
    long long query (int p) {
        long long all = 0;
        for (int i = p; i > 0; i -= (i & -i)) all += bit[i];
        return all;
    }
    int kth (long long k) {
        int ans = 0;
        for (int i = 1 << __lg(n); i > 0; i >>= 1) {
            if (ans + i <= n and bit[ans + i] < k) k -= bit[ans += i];
        }
        return ans + 1;
    }
};
