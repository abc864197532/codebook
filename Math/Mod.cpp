int add(int a, int b) { a += b; if (a >= mod) a -= mod; return a; }
int sub(int a, int b) { a -= b; if (a < 0) a += mod; return a; }
int mul(int a, int b) { return 1ll * a * b % mod; }
int mpow(int a, int b) { int ans = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) ans = mul(ans, a); return ans; }

int fac[N], facp[N], inv[N];

void build() {
    for (int i : {0, 1})
        fac[i] = facp[i] = inv[i] = 1;
    for (int i = 2; i < N; ++i) {
        inv[i] = sub(0, mul(inv[mod % i], mod / i));
        fac[i] = mul(fac[i - 1], i);
        facp[i] = mul(facp[i - 1], inv[i]);
    }
}

int C(int n, int m) {
    if (n < 0 || m < 0 || n < m)
        return 0;
    return mul(fac[n], mul(facp[m], facp[n - m]));
}