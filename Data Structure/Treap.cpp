struct Treap {
    int pri, sz, val;
    Treap *tl, *tr;
    Treap (int x) : val(x), sz(1), pri(rand()), tl(NULL), tr(NULL) {}
    void pull() {
        sz = (tl ? tl->sz : 0) + 1 + (tr ? tr->sz : 0);
    }
    void out() {
        if (tl)
            tl->out();
        cout << val << ' ';
        if (tr)
            tr->out();
    }
};

void print(Treap *t) {
    t->out();
    cout << endl;
}

Treap* merge(Treap *a, Treap *b) {
    if (!a || !b)
        return a ? a : b;
    if (a->pri < b->pri) {
        a->tr = merge(a->tr, b);
        a->pull();
        return a;
    } else {
        b->tl = merge(a, b->tl);
        b->pull();
        return b;
    }
}

void split(Treap* t, int k, Treap* &a, Treap* &b) {
    if (!t) a = b = NULL;
    else if ((t->tl ? t->tl->sz : 0) + 1 <= k) {
        a = t;
        split(t->tr, k - (t->tl ? t->tl->sz : 0) - 1, a->tr, b);
        a->pull();
    } else {
        b = t;
        split(t->tl, k, a, b->tl);
        b->pull();
    }
}