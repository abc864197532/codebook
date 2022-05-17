/* p == (a << n) + 1  
   g = pow(root, (p - 1) / n)
   n    1<<n        p          a    root
   5    32          97         3    5
   6    64          193        3    5
   7    128         257        2    3
   8    256         257        1    3
   9    512         7681       15   17
   10   1024        12289      12   11
   11   2048        12289      6    11
   12   4096        12289      3    11
   13   8192        40961      5    3
   14   16384       65537      4    3
   15   32768       65537      2    3
   16   65536       65537      1    3
   17   131072      786433     6    10
   18   262144      786433     3    10 (605028353, 2308, 3)
   19   524288      5767169    11   3
   20   1048576     7340033    7    3
   20   1048576     998244353  952  3
   21   2097152     23068673   11   3
   22   4194304     104857601  25   3
   23   8388608     167772161  20   3
   24   16777216    167772161  10   3
   25   33554432    167772161  5    3 (1107296257, 33, 10)
   26   67108864    469762049  7    3
*/

const int N = 1 << 20, mod = 998244353, G = 3;

long long modpow (long long a, int b) {
    long long ans = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1) ans = ans * a % mod;
    }
    return ans;
}

void run (vector <long long> &P, bool inv = false) {
    int N = P.size();
    const long long w = modpow(G, (mod - 1) / N);
    int lg = __lg(N);
    vector <int> rev(N);

    // bit reverse
    for (int i = 1; i < N; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        if (i < rev[i])
            swap(P[i], P[rev[i]]);
    }

    vector <long long> ws = {inv ? modpow(w, mod - 2) : w};
    for (int i = 1; i < lg; ++i) 
        ws.push_back(ws.back() * ws.back() % mod);
    reverse(ws.begin(), ws.end());

    for (int i = 0; i < lg; ++i) {
        for (int k = 0; k < N; k += (2 << i)) {
            long long base = 1;
            for (int j = k; j < k + (1 << i); ++j, base = base * ws[i] % mod) {
                long long t = base * P[j + (1 << i)] % mod, u = P[j];
                P[j] = u + t;
                if (P[j] >= mod) 
                    P[j] -= mod;
                P[j + (1 << i)] = u - t;
                if (P[j + (1 << i)] < 0) 
                    P[j + (1 << i)] += mod;
            }
        }
    }

    if (inv) {
        long long ninv = modpow(N, mod - 2);
        for (int i = 0; i < N; ++i) {
            P[i] = P[i] * ninv % mod;
        }
    }
}

vector <long long> mul (vector <long long> a, vector <long long> b) {
    int m = a.size() + b.size() - 1;
    int N = 1 << __lg(m) + 1;
    a.resize(N), b.resize(N);
    run(a), run(b);
    for (int i = 0; i < N; ++i) 
        a[i] = a[i] * b[i] % mod;
    run(a, true);
    a.resize(m);
    return a;
}