long long fac[N], facp[N], inv[N];

void build() {
	for (int i : {0, 1})
		fac[i] = facp[i] = inv[i] = 1;
	for (int i = 2; i < N; ++i) {
		inv[i] = mod - inv[mod % i] * (mod / i) % mod;
		fac[i] = fac[i - 1] * i % mod;
		facp[i] = facp[i - 1] * inv[i] % mod;
	}
}

long long C(int n, int m) {
	if (n < 0 || m < 0 || n < m)
		return 0;
	return fac[n] * facp[m] % mod * facp[n - m] % mod;
}

//==================================//

long long C[N][N];

void build() {
	C[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			if (C[i][j] >= mod)
				C[i][j] -= mod;
		}
	}
}

//==================================//

long long Catalan(int n) {
	return C(2 * n, n) * inv[n + 1] % mod;
}