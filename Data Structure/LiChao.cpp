struct Line {
	long long m, k; // y = mx + k
	long long v(int x) {
		return 1ll * m * x + k;
	}
};
 
struct LiChao {
	int l, r, m;
	vector <Line> v;
	Line line;
	LiChao* ch[2] = {NULL, NULL};
	LiChao (int l, int r) : l(l), r(r), m(l + r >> 1) {
		line.m = 0;
		line.k = 1ll << 60;
	} 
	void insert(Line seg) {
		if (r - l == 1) {
			if (seg.v(l) < line.v(l)) {
				line = seg;
			}
		} else {
		    if (m == 0) v.pb(seg);
			if (line.m > seg.m) swap(seg, line);
			if (line.v(m) > seg.v(m)) {
				swap(seg, line);
				if (!ch[1]) ch[1] = new LiChao(m, r);
				ch[1]->insert(seg);
			} else {
				if (!ch[0]) ch[0] = new LiChao(l, m);
				ch[0]->insert(seg);
			}
		}
	}
	long long query(int x) {
		if (r - l == 1) return line.v(x);
		if (x < m and ch[0]) return min(ch[0]->query(x), line.v(x));
		else if (x >= m and ch[1]) return min(ch[1]->query(x), line.v(x));
		else return line.v(x);
	}
};
