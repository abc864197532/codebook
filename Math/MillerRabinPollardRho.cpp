long long mul(long long x, long long y, long long p) {
    return (x * y - (long long)((long double)x / p * y) * p + p) % p;
}
lli modpow(lli a, lli b, lli m) {
    lli now = 1;
    for (; b; b >>= 1, a = mul(a, a, m)) {
        if (b & 1) now = mul(now, a, m);
    }
    return now;
}
bool MillerRabin(long long a, long long n) {
    if ((a = a % n) == 0) return 1;
    if ((n & 1) ^ 1) return n == 2;
    long long tmp = (n - 1) / ((n - 1) & (1 - n));
    long long t = __lg(((n - 1) & (1 - n))), x = 1;
    for (; tmp; tmp >>= 1, a = mul(a, a, n))
        if (tmp & 1) x = mul(x, a, n);
    if (x == 1 || x == n - 1) return 1;
    while (--t)
        if ((x = mul(x, x, n)) == n - 1) return 1;
    return 0;
}
// n < 4,759,123,141      3 : 2, 7, 61
// n < 1,122,004,669,633  4 : 2, 13, 23, 1662803
// n < 3,474,749,660,383  6 : primes <= 13
// n < 2^64             7 : 
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
bool prime(long long x) {
    if (x < 2) return false;
    vector <long long> v = {};
    for (long long a : v) if (a == x) return true;
    for (long long a : v) if (!MillerRabin(a, x)) return false;
    return true;
}
long long rho(long long p) {
    long long x, y, z, c, g;
    int i, j;
    while (true) {
        y = x = rand() % p, z = 1;
        c = rand() % p, i = 0, j = 1;
        while (++i) { 
            x = (mul(x, x, p) + c) % p;
            z = mul(z, abs(y - x), p);
            if (x == y || !z) break;
            if (!(i % 127) || i == j) {
                g = __gcd(z, p);
                if (g > 1) return g;
                if (i == j) y = x, j <<= 1;
            }
        }
    }
}
long long ans;
void prho(long long p) {
    if (p <= ans) return;
    if (prime(p)) {
        ans = p;
        return;
    }
    long long pi = rho(p);
    while (p % pi == 0) p /= pi;
    return prho(pi), prho(p);
}
vector <long long> p;
void PollardRho(long long n) {
    while (n > 1) {
        ans = 1;
        prho(n);
        if (ans == n) {
            p.push_back(n);
            break;
        }
        p.push_back(ans);
        while (n % ans == 0) n /= ans;
    }
}