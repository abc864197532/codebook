const int N = 100000;  

int lp[N], mu[N];

void build() {
    vector <int> p;
    for (int i = 2; i < N; ++i) {
        if (!lp[i]) {
            p.push_back(i);
            lp[i] = i;
        }
        for (int j = 0; 1ll * p[j] * i < N; ++j) {
            lp[p[j] * i] = p[j];
            if (i % p[j] == 0) break;
        }
    }
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (lp[i] == lp[i / lp[i]]) mu[i] = 0;
        else mu[i] = mu[i / lp[i]] * -1;
    }
}

