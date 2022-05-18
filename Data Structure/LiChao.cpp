struct line {
	long long m, k;
	line (long long _m, long long _k) : m(_m), k(_k) {}
	long long f(long long x) {return m * x + k;}
};

struct Seg {
	// query max
	// 0-indexed, [l, r)
	int l, r, m;
	line best;
	Seg* ch[2];
	Seg () = default;
	Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1), best(line(0, -1ll << 60)) {
		if (r - l > 1) {
			ch[0] = new Seg(l, m);
			ch[1] = new Seg(m, r);
		}
	}
	void add(line cur) {
		if (r - l == 1) {
			if (cur.f(l) > best.f(l)) {
				best = cur;
			}
		} else {
			if (cur.m < best.m)
				swap(cur, best);
			if (cur.f(m) > best.f(m)) {
				swap(cur, best);
				ch[0]->add(cur);
			} else {
				ch[1]->add(cur);
			}
		}
	}
	long long query(int x) {
		if (r - l == 1)
			return best.f(x);
		return max(best.f(x), ch[x >= m]->query(x));
	}
};

struct Seg {
	// query min
	// 0-indexed, [l, r)
	int l, r, m;
	line best;
	Seg* ch[2];
	Seg () = default;
	Seg (int _l, int _r) : l(_l), r(_r), m(l + r >> 1), best(line(0, 1ll << 60)) {
		if (r - l > 1) {
			ch[0] = new Seg(l, m);
			ch[1] = new Seg(m, r);
		}
	}
	void add(line cur) {
		if (r - l == 1) {
			if (cur.f(l) < best.f(l)) {
				best = cur;
			}
		} else {
			if (cur.m < best.m)
				swap(cur, best);
			if (cur.f(m) < best.f(m)) {
				swap(cur, best);
				ch[1]->add(cur);
			} else {
				ch[0]->add(cur);
			}
		}
	}
	long long query(int x) {
		if (r - l == 1)
			return best.f(x);
		return min(best.f(x), ch[x >= m]->query(x));
	}
};