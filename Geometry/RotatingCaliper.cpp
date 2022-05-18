long long RotatingCaliper(vector <Pt> &pt) {
    long long ans = INF;
    int n = pt.size();
    for (int i = 0, j = 2; i < n; ++i) {
        int ni = (i + 1) % n;
        while (true) {
            int nj = (j + 1) % n;
            // may need to change the function!
            if (area(pt[j], pt[i], pt[ni]) < area(pt[nj], pt[i], pt[ni])) {
                j = nj;
            } else {
                break;
            }
        }
        // update answer
    }
}