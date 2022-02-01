struct SMAWK {
    int ans[N], tmp[N];

    void interpolate(vector <int> l, vector <int> r) {
        int n = l.size(), m = r.size();
        vector <int> nl;
        for (int i = 1; i < n; i += 2) {
            nl.pb(l[i]);
        }
        run(nl, r);
        for (int i = 1, j = 0; i < n; i += 2) {
            while (j < m && r[j] < ans[l[i]])
                j++;
            assert(j < m && ans[l[i]] == r[j]);
            tmp[l[i]] = j;
        }
        for (int i = 0; i < n; i += 2) {
            int curl = 0, curr = m - 1;
            if (i)
                curl = tmp[l[i - 1]];
            if (i + 1 < n)
                curr = tmp[l[i + 1]];
            lli res = query(l[i], r[curl]);
            ans[l[i]] = r[curl];
            for (int j = curl + 1; j <= curr; ++j) {
                lli nxt = query(l[i], r[j]);
                if (res < nxt)
                    res = nxt, ans[l[i]] = r[j];
            }
        }
    }

    void reduce(vector <int> l, vector <int> r) {
        int n = l.size(), m = r.size();
        vector <int> nr;
        for (int j : r) {
            while (!nr.empty()) {
                int i = nr.size() - 1;
                if (query(l[i], nr.back()) <= query(l[i], j))
                    nr.pop_back();
                else
                    break;
            }
            if (nr.size() < n)
                nr.push_back(j);
        }
        run(l, nr);
    }

    void run(vector <int> l, vector <int> r) {
        int n = l.size(), m = r.size();
        if (max(n, m) <= 2) {
            for (int i : l) {
                ans[i] = r[0];
                if (m > 1) {
                    if (query(i, r[0]) < query(i, r[1]))
                        ans[i] = r[1];
                }
            }
        } else if (n >= m) {
            interpolate(l, r);
        } else {
            reduce(l, r);
        }
    }
} smawk;