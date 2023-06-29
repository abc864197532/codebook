// index 0 -> empty node
int val[M], l[M], r[M], sz;
int newNode(int x = 0) {
    if (x == 0) {
        val[sz] = 0, l[sz] = 0, r[sz] = 0;
    } else {
        val[sz] = val[x], l[sz] = l[x], r[sz] = r[x];
    }
    sz++;
    return sz - 1;
}
void pull(int id) {
    val[id] = val[l[id]] + val[r[id]];
}
int build(int tl, int tr, vector <int> &a) {
    int id = newNode();
    if (tr - tl == 1) {
        val[id] = a[tl];
    } else {
        l[id] = build(tl, tl + tr >> 1, a);
        r[id] = build(tl + tr >> 1, tr, a);
        pull(id);
    }
    return id;
}
int modify(int id, int v, int tl, int tr) {
    int x = newNode(id);
    if (tr - tl == 1) {
        val[x] = v;
    } else {
        if (v < (tl + tr >> 1)) {
            l[x] = modify(l[id], v, tl, tl + tr >> 1);
        } else {
            r[x] = modify(r[id], v, tl + tr >> 1, tr);
        }
        pull(x);
    }
    return x;
}
int query(int id, int a, int b, int tl, int tr) {
    if (!id) {
        return 0;
    }
    if (a <= tl && tr <= b) {
        return val[id];
    }
    int ans = 0;
    if (a < (tl + tr >> 1)) {
        ans += query(l[id], a, b, tl, tl + tr >> 1);
    }
    if ((tl + tr >> 1) < b) {
        ans += query(r[id], a, b, tl + tr >> 1, tr);
    }
    return ans;
}