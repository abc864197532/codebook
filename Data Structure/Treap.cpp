struct Treap {
    Treap *l, *r;
    int key, pri, sz;
    Treap (int _key) {
        key = _key;
        l = r = NULL;
        pri = rand();
        sz = 1;
    }
};

int size(Treap* t) {return t ? t->sz : 0;}
void pull(Treap* t) {t->sz = size(t->l) + 1 + size(t->r);}

Treap* merge(Treap* a, Treap* b) {
    if (!a or !b) return a ? a : b;
    else if (a->pri > b->pri) {
        a->r = merge(a->r, b);
        pull(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

void split(Treap* t, int k, Treap* &a, Treap* &b) {
    if (!t) a = b = NULL;
    else if (t->key <= k) {
        a = t;
        split(t->r, k, a->r, b);
        pull(a);
    } else {
        b = t;
        split(t->l, k, a, b->l);
        pull(b);
    }
}

Treap* insert(Treap* t, int k) {
    Treap *tl, *tr;
    split(t, k, tl, tr);
    return merge(tl, merge(new Treap(k), tr));
}

Treap* remove(Treap* t, int k) {
    Treap *tl, *tr;
    split(t, k - 1, tl, t);
    split(t, k, t, tr);
    return merge(tl, tr);
}

int kth(Treap* t, int k) {
    if (size(t->l) + 1 < k) {
        return kth(t->r, k - size(t->l) - 1);
    } else if (size(t->l) == k) {
        return t->key;
    } else {
        return kth(t->l, k);
    }
}

int index(Treap* t, int x) {
    if (!t) return -1;
    if (t->key > x) {
        return index(t->l, x);
    } else if (t->key == x) {
        return size(t->l);
    } else {
        int k = index(t->r, x);
        return k == -1 ? -1 : size(t->l) + 1 + k;
    }
}
