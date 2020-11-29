vector <int> build_sa (string s) {
    s += '$';
    int n = s.length();
    vector <int> r(n), sa(n);
    iota(all(sa), 0);
    sort(all(sa), [&](int i, int j) {return s[i] < s[j];});
    r[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (s[sa[i - 1]] == s[sa[i]]) r[sa[i]] = r[sa[i - 1]];
        else r[sa[i]] = r[sa[i - 1]] + 1;
    }
    for (int k = 0; (1 << k) < n; k++) {
        vector <int> nsa(n), nr(n);
        for (int i = 0; i < n; ++i) nsa[i] = (sa[i] - (1 << k) + n) % n;
        vector <int> cnt(n, 0);
        for (int i = 0; i < n; ++i) cnt[r[i]]++;
        for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[r[nsa[i]]]] = nsa[i];
        nr[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (r[sa[i - 1]] == r[sa[i]] && r[(sa[i - 1] + (1 << k)) % n] == r[(sa[i] + (1 << k)) % n]) nr[sa[i]] = nr[sa[i - 1]];
            else nr[sa[i]] = nr[sa[i - 1]] + 1;
        }
        swap(r, nr);
    }
    return sa;
}

vector <int> build_he(string &s) {
    int n = s.length();
    vector <int> sa = build_sa(s), r(n), h(n - 1);
    for (int i = 0; i < n; ++i) r[sa[i]] = i;
    for (int i = 0, k = 0; i < n - 1; ++i, k = max(k - 1, 0)) {
        while (s[i + k] == s[sa[r[i] - 1] + k]) k++;
        h[r[i] - 1] = k;
    }
    return h;
}
