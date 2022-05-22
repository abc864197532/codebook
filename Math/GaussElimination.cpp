long long modpow(long long a, int b) {
    long long ans = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1) ans = ans * a % mod;
    }
    return ans;
}

vector <int> GaussElimination(vector <vector <long long>> a) {
    // only for n equations and n variables
    // return empty if wrong
    int n = a.size();
    assert(n + 1 == a[0].size());
    for (int i = 0; i < n; ++i) {
        if (a[i][i] == 0) {
            bool is = false;
            for (int j = i + 1; j < n; ++j) if (a[j][i]) {
                swap(a[j], a[i]);
                is = true;
                break;
            }
            if (!is)
                return {};
        }
        long long mul = modpow(a[i][i], mod - 2);
        for (int j = 0; j <= n; ++j)
            a[i][j] = a[i][j] * mul % mod;
        for (int j = 0; j < n; ++j) if (i ^ j) {
            int mul = a[j][i];
            for (int k = 0; k <= n; ++k) {
                a[j][k] -= a[i][k] * mul % mod;
                if (a[j][k] < 0)
                    a[j][k] += mod;
            }
        }
    }
    vector <int> ans(n);
    for (int i = 0; i < n; ++i)
        ans[i] = a[i][n];
    return ans;
}