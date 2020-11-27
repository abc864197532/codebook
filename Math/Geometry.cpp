struct Pt {
	long long x, y;
	Pt (long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
	Pt operator + (const Pt &other) {
		return Pt(x + other.x, y + other.y);
	}
	Pt operator - (const Pt &other) {
		return Pt(x - other.x, y - other.y);
	}
	Pt operator * (const int &k) {
		return Pt(x * k, y * k);
	}
	long long operator * (const Pt &other) { // dot
		return x * other.x + y * other.y;
	}
	long long operator ^ (const Pt &other) { // cross
		return x * other.y - y * other.x;
	}
};

int ori (Pt o, Pt a, Pt b) {
	long long k = (o - a) ^ (o - b);
	return (k < 0 ? -1 : (k > 0 ? 1 : 0));
}

bool banana (Pt a, Pt b, Pt c, Pt d) { // check segment ab and cd
	if (ori(a, b, c) == 0 and (c - a) * (c - b) <= 0) return true;
	if (ori(a, b, d) == 0 and (d - a) * (d - b) <= 0) return true;
	if (ori(c, d, a) == 0 and (a - c) * (a - d) <= 0) return true;
	if (ori(c, d, b) == 0 and (b - c) * (b - d) <= 0) return true;
	if (ori(a, b, c) * ori(a, b, d) == -1 and ori(c, d, a) * ori(c, d, b) == -1) return true;
	return false;
}

vector <Pt> get_down_convex_hull (vector <Pt> &point) {
	int n = point.size();
	sort(all(point), [](Pt a, Pt b) {
		if (a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	});
	auto check = [&](Pt a, Pt b, Pt c) {
		return ((a - b) ^ (a - c)) <= 0;
	};
	vector <Pt> ans;
	for (int i = 0; i < n; ++i) {
		while (ans.size() >= 2 and check(ans[ans.size() - 2], ans.back(), point[i])) {
			ans.pop_back();
		}
		ans.pb(point[i]);
	}
	return ans;
}

vector <Pt> get_up_convex_hull (vector <Pt> &point) {
	int n = point.size();
	sort(all(point), [](Pt a, Pt b) {
		if (a.x == b.x) return a.y > b.y;
		return a.x > b.x;
	});
	auto check = [&](Pt a, Pt b, Pt c) {
		return ((b - a) ^ (c - a)) <= 0;
	};
	vector <Pt> ans;
	for (int i = 0; i < n; ++i) {
		while (ans.size() >= 2 and check(ans[ans.size() - 2], ans.back(), point[i])) {
			ans.pop_back();
		}
		ans.pb(point[i]);
	}
	return ans;
}
