struct Sieve {
    int lp[N], mu[N];
    Sieve () {
        vector <int> p;
        for (int i = 2; i < N; ++i) {
            if (!lp[i]) {
                p.push_back(i);
                lp[i] = i;
            }
            for (int j = 0; 1ll * p[j] * i < N; ++j) {
                lp[p[j] * i] = p[j];
                if (i % p[j] == 0) 
                    break;
            }
        }
        mu[1] = 1;
        for (int i = 2; i < N; ++i) {
            if (lp[i] == lp[i / lp[i]]) 
                mu[i] = 0;
            else 
                mu[i] = mu[i / lp[i]] * -1;
        }
    }
    vector <pair <int, int>> pfactor(int x) {
        vector <pair <int, int>> now;
        while (x > 1) {
            int p = lp[x];
            if (!now.empty() && now.back().first == p)
                now.back().second++;
            else
                now.emplace_back(x, 1);
            x /= p;
        }
        return now;
    }
    vector <int> factor(int x) {
        vector <int> now = {1};
        while (x > 1) {
            int p = lp[x], cnt = 0;
            while (x % p == 0)
                cnt++, x /= p;
            vector <int> nxt;
            for (int i = 0, cur = 1; i <= cnt; ++i) {
                for (int j : now)
                    nxt.push_back(cur * j);
                cur *= p;
            }
            now = nxt;
        }
        sort(all(now));
        return now;
    }
};