struct mat {
    int n;
    long long mod2;
    vector <vector <long long>> val;
    mat () = default;
    mat (int _n, int _mode = 0) : n(_n), mod2(1ll * mod * mod) {
        // mode 1 -> I, other -> O
        val.assign(n, vector<long long>(n, 0));
        if (_mode == 1) {
            for (int i = 0; i < n; ++i) val[i][i] = 1;
        }
    }
    mat (const mat& M) : n(M.n), mod2(1ll * mod * mod) {
        val.assign(n, vector<long long>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                val[i][j] = M.val[i][j];
            }
        }
    }
    mat (vector <vector <long long>> v) : n(v.size()), mod2(1ll * mod * mod), val(v) {}
    mat operator + (const mat& o) {
        mat ans(o);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans.val[i][j] += val[i][j];
                if (ans.val[i][j] >= mod) ans.val[i][j] -= mod;
            }
        }
        return ans;
    }
    mat operator * (const mat& o) {
        mat ans(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                for (int j = 0; j < n; ++j) {
                    ans.val[i][j] += val[i][k] * o.val[k][j];
                    if (ans.val[i][j] >= mod2) ans.val[i][j] -= mod2;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans.val[i][j] %= mod;
            }
        }
        return ans;
    }
    mat operator ^ (long long k) {
        mat ans(n, 1), a(*this);
        for (; k; k >>= 1, a = a * a) {
            if (k & 1) ans = ans * a;
        }
        return ans;
    }
    mat& operator = (mat o) {
        this->n = o.n, this->val = o.val, this->mod2 = o.mod2;
        return *this;
    }
};