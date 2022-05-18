struct DynamicConvexHull {
	struct Up_cmp {
	    bool operator () (const Pt a, const Pt b) {
	        if (a.x == b.x)
	            return a.y < b.y;
	        return a.x < b.x;
	    }
	};
	struct Down_cmp {
	    bool operator () (const Pt a, const Pt b) {
	        if (a.x == b.x)
	            return a.y > b.y;
	        return a.x > b.x;
	    }
	};
	template <typename T>
	struct Hull {
	    set <Pt, T> hull;
	    bool chk(Pt i, Pt j, Pt k) {
	        return ((k - i) ^ (j - i)) > 0;
	    }
	    void insert(Pt x) {
	        if (inside(x))
	            return;
	        hull.insert(x);
	        auto it = hull.lower_bound(x);
	        if (next(it) != hull.end()) {
	            for (auto it2 = next(it); next(it2) != hull.end(); ++it2) {
	                if (chk(x, *it2, *next(it2)))
	                    break;
	                hull.erase(it2);
	                it2 = hull.lower_bound(x);
	            }
	        }
	        it = hull.lower_bound(x);
	        if (it != hull.begin()) {
	            for (auto it2 = prev(it); it2 != hull.begin(); --it2) {
	                if (chk(*prev(it2), *it2, x)) 
	                    break;
	                hull.erase(it2);
	                it2 = hull.lower_bound(x);
	                if (it2 == hull.begin())
	                    break;
	            }
	        }
	    }
	    bool inside(Pt x) {
	        if (hull.lower_bound(x) != hull.end() && *hull.lower_bound(x) == x)
	            return true;
	        auto it = hull.lower_bound(x);
	        bool ans = false;
	        if (it != hull.begin() && it != hull.end()) {
	            ans = !chk(*prev(it), x, *it);
	        }
	        return ans;
	    }
	};
	Hull <Up_cmp> up;
	Hull <Down_cmp> down;
	void insert(Pt x) {
	    up.insert(x), down.insert(x);
	}
	bool inside(Pt x) {
	    return up.inside(x) && down.inside(x);
	}
};