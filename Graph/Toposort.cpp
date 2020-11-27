const int N = 100000;

vector <int> adj[N], deg(N, 0);

vector <int> toposort(int n) {
	vector <int> d(n), ans;
	queue <int> q;
	for (int i = 0; i < n; ++i) {
		d[i] = deg[i];
		if (d[i] == 0) {
			q.push(i);
		}
	}
	while (q.size()) {
		int v = q.front(); q.pop();
		ans.push_back(v);
		for (int u : adj[v]) {
			d[u]--;
			if (d[u] == 0) q.push(u);
		}
	}
	if (ans.size() != n) {
		ans.clear();
		ans.push_back(-1);
	}
	return ans;
}
