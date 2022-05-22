long long modpow(long long a, long long b, int m) {
    long long ans = 1;
    for (; b; b >>= 1, a = a * a % m) {
        if (b & 1)
            ans = ans * a % m;
    }
    return ans;
}

struct LinearEquationSolver {
    vector <vector <int>> basis;
    vector <bool> isEmpty;
    int n, mod;
    LinearEquationSolver (int _n, int _mod) : n(_n), mod(_mod) {
        basis.assign(n, vector <int> (n + 1, 0));
        isEmpty.assign(n, true);
    }
    bool add(vector <int> vec) {
        // vec.size() = n + 1
        for (int i = 0; i < n; ++i) if (vec[i]) {
            if (isEmpty[i]) {
                basis[i] = vec;
                isEmpty[i] = false;
                return true;
            }
            int k = 1ll * vec[i] * modpow(basis[i][i], mod - 2, mod) % mod;
            for (int j = 0; j <= n; ++j) {
                vec[j] -= 1ll * basis[i][j] * k % mod;
                if (vec[j] < 0)
                    vec[j] += mod;
            }
        }
        return vec[n] == 0;
    }
    vector <int> solve() {
        vector <int> ans(n);
        for (int i = n - 1; ~i; --i) {
            if (!isEmpty[i]) {
                ans[i] = basis[i][n];
                for (int j = i + 1; j < n; ++j) {
                    ans[i] -= 1ll * basis[i][j] * ans[j] % mod;
                    if (ans[i] < 0)
                        ans[i] += mod;
                }
                ans[i] = 1ll * ans[i] * modpow(basis[i][i], mod - 2, mod) % mod;
            } else {
                ans[i] = 0;
            }
        }
        return ans;
    }
};