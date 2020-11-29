const int N = 100000, logN = 17;  

int StMn[N][logN], StMx[N][logN];

void buildSt() {
    for (int j = 1; j < logN; ++j) {
        for (int i = 0; i + (1 << j) <= N; ++i) {
            StMn[i][j] = min(StMn[i][j - 1], StMn[i + (1 << j - 1)][j - 1]);
            StMx[i][j] = max(StMx[i][j - 1], StMx[i + (1 << j - 1)][j - 1]);
        }
    }
}

int queryMn(int l, int r) {
    int g = __lg(r - l);
    return min(StMn[l][g], StMn[r - (1 << g)][g]);
}

int queryMx(int l, int r) {
    int g = __lg(r - l);
    return max(StMx[l][g], StMx[r - (1 << g)][g]);
}
