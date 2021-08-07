struct or_convolution {
    void fwt(vector <int> &a) {
        int n = __lg(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                if (j >> i & 1) a[j] += a[j ^ (1 << i)];
            }
        }
    }
    void ifwt(vector <int> &a) {
        int n = __lg(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                if (j >> i & 1) a[j] -= a[j ^ (1 << i)];
            }
        }
    }
};

struct and_convolution {
    void fwt(vector <int> &a) {
        int n = __lg(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                if (~j >> i & 1) a[j] += a[j ^ (1 << i)];
            }
        }
    }
    void ifwt(vector <int> &a) {
        int n = __lg(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 1 << n; ++j) {
                if (~j >> i & 1) a[j] -= a[j ^ (1 << i)];
            }
        }
    }
};

struct xor_convolution {
    void fwt(vector <int> &a) {
        int n = __lg(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 1 << n; ++j) if (j >> i & 1) {
                int x = a[j ^ (1 << i)], y = a[j];
                a[j ^ (1 << i)] = x + y;
                a[j] = x - y;
            }
        }
    }
    void ifwt(vector <int> &a) {
        int n = __lg(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 1 << n; ++j) if (j >> i & 1) {
                int x = a[j ^ (1 << i)], y = a[j];
                a[j ^ (1 << i)] = (x + y) / 2;
                a[j] = (x - y) / 2;
            }
        }
    }
};
