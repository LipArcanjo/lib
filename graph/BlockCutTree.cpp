struct block_cut_tree {
	vector<vector<int>> g, blocks, tree; //input graphs, nodes in block, blockcuttree 
	vector<vector<pair<int, int>>> edgblocks; //edges on the blocks
	stack<int> s;
	stack<pair<int, int>> s2;
	vector<int> id, art, pos, rev;
 
	block_cut_tree(vector<vector<int>> g_) : g(g_) {
		int n = g.size();
		id.resize(n, -1), art.resize(n), pos.resize(n);
		build();
	}
 
	int dfs(int i, int& t, int p = -1) {
		int lo = id[i] = t++;
		s.push(i);
		if (p != -1) s2.emplace(i, p);
		for (int j : g[i]) if (j != p and id[j] != -1)
			s2.emplace(i, j);
 
		for (int j : g[i]) if (j != p) {
			if (id[j] == -1) {
				int val = dfs(j, t, i);
				lo = min(lo, val);
				if (val >= id[i]) {
					art[i]++;
					blocks.emplace_back(1, i);
					while (blocks.back().back() != j)
						blocks.back().push_back(s.top()), s.pop();
					edgblocks.emplace_back(1, s2.top()), s2.pop();
					while (edgblocks.back().back() != pair(j, i))
						edgblocks.back().push_back(s2.top()), s2.pop();
				}
			}
			else lo = min(lo, id[j]);
		}
 
		if (p == -1 and art[i]) art[i]--;
		return lo;
	}
 
	void build() {
		int t = 0;
		for (int i = 0; i < g.size(); i++) if (id[i] == -1) dfs(i, t, -1);
		tree.resize(blocks.size());
		rev.resize(blocks.size());
		for (int i = 0; i < g.size(); i++) if (art[i])
			pos[i] = tree.size(), rev.push_back(i), tree.emplace_back();
		for (int i = 0; i < blocks.size(); i++) for (int j : blocks[i]) {
			if (!art[j]) pos[j] = i;
			else tree[i].push_back(pos[j]), tree[pos[j]].push_back(i);
		}
	}
};
