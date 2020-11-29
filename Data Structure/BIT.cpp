const int N = 100000;

struct BIT {
    long long bit[N];
    BIT ()  {
        for (int i = 0; i < N; ++i) bit[i] = 0;
    }
    void add (int p, long long a) {
        for (int i = p; i < N; i += (i & -i)) bit[i] += a;
    }
    long long query (int p) {
        long long all = 0;
        for (int i = p; i > 0; i -= (i & -i)) all += bit[i];
        return all;
    }
    int kth (long long k) {
        int ans = 0;
        for (int i = 1 << __lg(N); i > 0; i >>= 1) {
            if (ans + i < N and bit[ans + i] < k) k -= bit[ans += i];
        }
        return ans + 1;
    }
};
