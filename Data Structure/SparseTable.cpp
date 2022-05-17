template <typename T>
struct SparseTableMax {
    // 0-indexed, [l, r)
    vector <vector <T>> table;
    SparseTableMax (vector <T> a) {
        int n = a.size();
        int m = __lg(n) + 1;
        table.resize(n, vector <T> (m, 0));
        for (int i = 0; i < n; ++i)
            table[i][0] = a[i];
        for (int j = 1; j < m; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                table[i][j] = max(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    T query(int l, int r) {
        if (l >= r)
            return -1 << 30;
        int g = __lg(r - l);
        return max(table[l][g], table[r - (1 << g)][g]);
    }
};

template <typename T>
struct SparseTableMin {
    // 0-indexed, [l, r)
    vector <vector <T>> table;
    SparseTableMin (vector <T> a) {
        int n = a.size();
        int m = __lg(n) + 1;
        table.resize(n, vector <T> (m, 0));
        for (int i = 0; i < n; ++i)
            table[i][0] = a[i];
        for (int j = 1; j < m; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                table[i][j] = min(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    T query(int l, int r) {
        if (l >= r)
            return 1 << 30;
        int g = __lg(r - l);
        return min(table[l][g], table[r - (1 << g)][g]);
    }
};