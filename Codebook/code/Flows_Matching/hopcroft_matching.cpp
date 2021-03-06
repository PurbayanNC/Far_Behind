struct graph {// O(m * \sqrt{n}) // 0-indexed vertices
	int L, R; vector<vector<int>> adj;
	graph(int L, int R) : L(L), R(R), adj(L+R) {}
	void add_edge(int u, int v) {
		adj[u].pb(v+L); adj[v+L].pb(u);}
	int maximum_matching(){
		vector<int> level(L), mate(L+R, -1);
		function<bool(void)> levelize = [&]() { // BFS
			queue<int> Q;
			for (int u = 0; u < L; ++u) {
				level[u] = -1;
				if (mate[u] < 0) level[u] = 0, Q.push(u);
			}
			while (!Q.empty()) {
				int u = Q.front(); Q.pop();
				for (int w: adj[u]) {
					int v = mate[w];
					if (v < 0) return true;
					if (level[v] < 0)
						level[v] = level[u] + 1, Q.push(v);
				}
			}return false;
		};
		function<bool(int)> augment=[&](int u){//DFS
			for (int w: adj[u]) {
				int v = mate[w];
				if(v<0||(level[v]>level[u]&&augment(v))){
					mate[u] = w; mate[w] = u;return true;
				}
			}return false;
		};
		int match = 0;
		while (levelize()) 
			for (int u = 0; u < L; ++u) 
				if (mate[u] < 0 && augment(u)) ++match;
		return match;
	}
}; // L-left size, R->right size
graph g(L,R); g.add_edge(u,v); g.max_matching();