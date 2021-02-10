const long double pi = acos(-1), eps = 1e-14;
typedef complex<long double> cp;

struct FFT {
    int n, rev[N];
    cp omega[N], iomega[N];
    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; ++i) {
            omega[i] = cp(cos(pi * 2 / n * i), sin(pi * 2 / n * i));
            iomega[i] = conj(omega[i]);
        }
        int k = __lg(n);
        for (int i = 0; i < n; ++i) {
            int t = 0;
            for (int j = 0; j < k; ++j) {
                if (i & (1 << j)) t |= (1 << k - j - 1);
            }
            rev[i] = t;
        }
    }
    void transform(vector<cp> &a, cp *xomega) {
        for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int len = 2; len <= n; len <<= 1) {
            int mid = len >> 1;
            int r = n / len;
            for (int j = 0; j < n; j += len) {
                for (int i = 0; i < mid; ++i) {
                    cp t = xomega[r * i] * a[j + mid + i];
                    a[j + mid + i] = a[j + i] - t;
                    a[j + i] += t;
                }
            }
        }
    }
    void fft(vector<cp> &a) { transform(a, omega); }
    void ifft(vector<cp> &a) {
        transform(a, iomega);
        for (int i = 0; i < n; ++i) a[i] /= n;
    }
};
