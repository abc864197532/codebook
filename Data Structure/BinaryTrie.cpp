struct Trie {  
    vector <vector <int>> ch;
    vector <int> cnt;
    Trie() {extend();}
    void extend() {
        ch.pb(vector <int>(2, 0));
        cnt.pb(0);
    }
    int next(int u, int v) {
        if (!ch[u][v]) {
            ch[u][v] = ch.size();
            extend();
        }
        return ch[u][v];
    }
    void insert(int x) {
        int now = 0;
        for (int d = 30; ~d; --d) {
            now = next(now, x >> d & 1);
        }
        cnt[now]++;
    }
    int query(int x) {
        // query max (x xor y)
        int ans = 0, now = 0;
        for (int d = 30; ~d; --d) {
            if (ch[now][~x >> d & 1]) {
                now = ch[now][~x >> d & 1];
                ans |= 1 << d;
            } else {
                now = ch[now][x >> d & 1];
            }
        }
        return ans;
    }
};