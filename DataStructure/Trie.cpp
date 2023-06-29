struct Trie {
    int ch[M][26], cnt[M], sz;
    Trie() { extend(); }
    void extend() {
        for (int i = 0; i < 26; ++i) {
            ch[sz][i] = 0;
        }
        cnt[sz] = 0, sz++;
    }
    void reset() { sz = 0, extend(); }
    int next(int u, int v) {
        if (!ch[u][v]) {
            ch[u][v] = sz;
            extend();
        }
        return ch[u][v];
    }
    void add(sting s) {
        int now = 0;
        for (char c : s) {
            now = next(now, c - 'a');
        }
        cnt[now]++;
    }
    void del(sting s) {
        int now = 0;
        for (char c : s) {
            now = next(now, c - 'a');
        }
        cnt[now]--;
    }
};