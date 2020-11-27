template <typename T>
struct Dinic {
	const T INF = 0x3f3f3f3f;
	struct Edge {
		int v, id;
		T f;
		Edge(int _v, T _f, int _id) : v(_v), id(_id), f(_f) {}
	};
	
	vector <vector <Edge>> adj;
	vector <int> level;
	int n, s, t;
	
	Dinic (int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
		adj.resize(n);
		level.resize(n);
	}
	
	void add_edge(int u, int v, T f) {
		adj[u].push_back(Edge(v, f, adj[v].size()));
		adj[v].push_back(Edge(u, 0, adj[u].size() - 1));
	}
	
	bool bfs() {
		for (int i = 0; i < n; ++i) level[i] = -1;
		queue <int> q;
		q.push(s);
		level[s] = 0;
		while (q.size()) {
			int v = q.front(); q.pop();
			for (Edge e : adj[v]) {
				if (e.f > 0 and level[e.v] == -1) {
					level[e.v] = level[v] + 1;
					q.push(e.v);
				}
			}
		}
		return level[t] != -1;
	}
	
	T dfs(int v, T minf) {
		if (v == t) return minf;
		T ans = 0;
		for (Edge &e : adj[v]) {
			if (e.f > 0 and level[e.v] == level[v] + 1) {
				T nxtf = dfs(e.v, min(minf, e.f));
				ans += nxtf;
				minf -= nxtf;
				e.f -= nxtf;
				adj[e.v][e.id].f += nxtf;
				if (minf == 0) return ans;
			}
		}
		if (!ans) level[v] = -1;
		return ans;
	}
	
	T runFlow() {
		T ans = 0;
		while (bfs()) {
			ans += dfs(s, INF);
		}
		return ans;
	}
};
