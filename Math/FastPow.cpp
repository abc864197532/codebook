long long modpow(long long a, int b) {
    long long ans = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1) ans = ans * a % mod;
    }
    return ans;
}

long long modinv(long long a) {return modpow(a, mod - 2);}
