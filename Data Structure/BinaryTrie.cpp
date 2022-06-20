struct Trie {
    int ch[M][2], cnt[M], sz;
    Trie() {extend();}
    void extend() {
        ch[sz][0] = ch[sz][1] = cnt[sz] = 0, sz++;
    }
    int next(int u, int v) {
        if (!ch[u][v]) {
            ch[u][v] = sz;
            extend();
        }
        return ch[u][v];
    }
    void add(int x) {
        int now = 0;
        for (int d = 29; ~d; --d) {
            now = next(now, x >> d & 1);
            cnt[now]++;
        }
    }
    void del(int x) {
        int now = 0;
        for (int d = 29; ~d; --d) {
            now = next(now, x >> d & 1);
            cnt[now]--;
        }
    }
    int query(int x) {
        // query max (x xor y)
        int ans = 0, now = 0;
        for (int d = 29; ~d; --d) {
            if (cnt[ch[now][~x >> d & 1]]) {
                now = ch[now][~x >> d & 1];
                ans |= 1 << d;
            } else if (cnt[ch[now][x >> d & 1]]) {
                now = ch[now][x >> d & 1];
            }
        }
        return ans;
    }
};