/*finds min weighted cut in undirected graph in
O(n^3), Adj Matrix, 0-indexed vertices
output-(min cut value, nodes in half of min cut)*/
typedef vector<int> VI;typedef vector<VI> VVI;
const int INF = 1e9;
pair<int, VI> GetMinCut(VVI &weights) {
	int N = weights.size();
	VI used(N), cut, best_cut;
	int best_weight = -1;
	for (int phase = N-1; phase >= 0; phase--) {
		VI w = weights[0];
		VI added = used;
		int prev, last = 0;
		for (int i = 0; i < phase; i++) {
			prev = last; last = -1;
			for (int j = 1; j < N; j++)
			if(!added[j] && (last==-1 || w[j]>w[last])) 
				last = j;
			if (i == phase-1) {
				for(int j=0;j<N;j++) 
					weights[prev][j] += weights[last][j];
				for(int j=0;j<N;j++) 
					weights[j][prev] = weights[prev][j];
				used[last] = true; cut.push_back(last);
				if(best_weight==-1 || w[last]<best_weight)
					best_cut = cut, best_weight = w[last];
			}
			else {
				for (int j = 0; j < N; j++)
				w[j] += weights[last][j];
				added[last] = true;
			}
		}
	}
	return make_pair(best_weight, best_cut);
}
VVI weights(n, VI(n));
pair<int, VI> res = GetMinCut(weights);