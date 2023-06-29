ll add(ll a, ll b) {a += b; if (a >= mod) a -= mod; return a;}
ll sub(ll a, ll b) {a -= b; if (a < 0) a += mod; return a;}
ll mul(ll a, ll b) {return a * b % mod;}
ll mpow(ll a, ll b) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1) {
            ans = ans * a % mod;
        }
    }
    return ans;
}

struct NTT {
  ll w[N];
  NTT() {
    ll dw = mpow(G, (mod - 1) / N);
    w[0] = 1;
    for (int i = 1; i < N; ++i) w[i] = mul(w[i - 1], dw);
  }
  void operator()(vector<ll>& a, bool inv = false) { //0 <= a[i] < P
    int x = 0, n = a.size();
    for (int j = 1; j < n - 1; ++j) {
      for (int k = n >> 1; (x ^= k) < k; k >>= 1);
      if (j < x) swap(a[x], a[j]);
    }
    for (int L = 2; L <= n; L <<= 1) {
      int dx = N / L, dl = L >> 1;
      for (int i = 0; i < n; i += L) {
        for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
          ll tmp = mul(a[j + dl], w[x]);
          a[j + dl] = sub(a[j], tmp);
          a[j] = add(a[j], tmp);
        }
      }
    }
    if (inv) {
      reverse(a.begin() + 1, a.end());
      ll invn = mpow(n, mod - 2);
      for (int i = 0; i < n; ++i) a[i] = mul(a[i], invn);
    }
  }
} ntt;

vector <ll> Mul(vector <ll> a, vector <ll> b, int bound = N) {
  int m = a.size() + b.size() - 1, n = 1;
  while (n < m) n <<= 1;
  a.resize(n), b.resize(n);
  ntt(a), ntt(b);
  vector <ll> out(n);
  for (int i = 0; i < n; ++i) out[i] = mul(a[i], b[i]);
  ntt(out, true), out.resize(min(m, bound));
  return out;
}