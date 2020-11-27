const int mod = 1e9 + 7;

long long modpow(int a, int b) {
	long long ans = 1;
	for (long long aa = a; b; b >>= 1, aa = aa * aa % mod) {
		if (b & 1) ans = ans * aa % mod;
	}
	return ans;
}

long long modinv (int b) {
	return modpow(b, mod - 2);
}
