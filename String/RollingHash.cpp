struct RollingHash {
    string s;
    int n, c, mod;
    vector <long long> pre, pw;
    RollingHash(string _s, int _c, int _mod) : s(_s), n(s.length()), c(_c), mod(_mod) {
        pre.resize(n + 1, 0);
        pw.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = ((pre[i - 1] * c) + s[i]) % mod;
        }
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i - 1] * c % mod;
        }
    }
    long long query(int l, int r) {
        return (pre[r] - ((pre[l] * pw[r - l]) % mod) + mod) % mod;
    }
};
