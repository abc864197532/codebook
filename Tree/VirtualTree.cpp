vector <int> newadj[N];

vector <int> build_virtual_tree(vector <int> a) {
    // need lca
    int sz = a.size();
    sort(all(a), [&](int i, int j) {return LCA.in[i] < LCA.in[j];});
    for (int i = 1; i < sz; ++i) {a.pb(LCA.lca(a[i - 1], a[i]));}
    sort(all(a), [&](int i, int j) {return LCA.in[i] < LCA.in[j];});
    a.resize(unique(a.begin(), a.end()) - a.begin());
    for (int i = 1; i < a.size(); ++i) {
        int u = LCA.lca(a[i - 1], a[i]), v = a[i];
        newadj[u].push_back(v), newadj[v].push_back(u);
    }
    return a;
}