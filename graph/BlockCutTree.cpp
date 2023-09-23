#include <bits/stdc++.h>
 
using namespace std;
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
 
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
 
struct block_cut_tree {
	vector<vector<int>> g, blocks, tree;
	vector<vector<pair<int, int>>> edgblocks;
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
	vector<vector<ll>> dp;
	
	ll solve(int i, int p, int used, int type) { 
		ll &ret = dp[i][used];
		if (ret != -1) return ret;
		ret = 0;
		
		if (type == 0) { // block
			assert(blocks[i].size()*(blocks[i].size()-1)/2 == edgblocks[i].size());
			int cur = blocks[i].size() - tree[i].size(); // vertices que nao sao cut
			cur += used; // esse cut é usado aqui
			ret = INF;
			vector<ll> dif;
			ll cur_val = 0;
			for (int j : tree[i]) if (j != p) {
				cur_val += solve(j, i, 0, !type);
				dif.push_back(solve(j, i, 1, !type) - solve(j, i, 0, !type));
			}
			if (cur == 0) ret = cur_val;
			else if (cur >= 3) ret = 1 + cur_val;
			sort(dif.begin(), dif.end());
			for (ll val : dif) {
				cur++;
				cur_val += val;
				if (cur >= 3) ret = min(ret, 1 + cur_val);
			}
			return ret;
		}
		else { // art
			if (used) {
				for (int j : tree[i]) if (j != p) {
					ret += solve(j, i, 0, !type);
				}
			}
			else {
				ll min_dif = INF;
				for (int j : tree[i]) if (j != p) {
					ret += solve(j, i, 0, !type);
					min_dif = min(min_dif, solve(j, i, 1, !type) 
										   - solve(j, i, 0, !type));
				}
				ret += min_dif;
			}
		}
		return ret;
	}
 
	void rec(int i, int p, int used, int type, vector<vector<int>> &ret) { 
		if (type == 0) { // block
			assert(blocks[i].size()*(blocks[i].size()-1)/2 == edgblocks[i].size());
			int cur = blocks[i].size() - tree[i].size(); // vertices que nao sao cut
			cur += used; // esse cut é usado aqui
			
			vector<int> clique;
			for (int j : blocks[i]) if (!art[j]) clique.push_back(j);
			if (used) clique.push_back(rev[p]);
 
			vector<pair<ll, int>> dif;
			ll cur_val = 0;
			for (int j : tree[i]) if (j != p) {
				cur_val += solve(j, i, 0, !type);
				dif.emplace_back(solve(j, i, 1, !type) - solve(j, i, 0, !type), j);
			}
			
			int id_min = -1;
			sort(dif.begin(), dif.end());
			for (auto [val, j] : dif) {
				cur++;
				cur_val += val;
				if (cur >= 3) {
					if (1 + cur_val == dp[i][used]) id_min = j;
				}
			}
			
			if (id_min == -1) {
				for (int j : tree[i]) if (j != p) {
					rec(j, i, 0, !type, ret);
				}
				if (clique.size()) ret.push_back(clique);
			}
			else {
				bool reach = false;
				for (auto [val, j] : dif) {
					if (!reach) {
						clique.push_back(rev[j]);
						rec(j, i, 1, !type, ret);
					}
					else {
						rec(j, i, 0, !type, ret);
					}
					if (j == id_min) reach = true;
				}
				ret.push_back(clique);
			}
		}
		else { // art
			if (used) {
				for (int j : tree[i]) if (j != p) {
					rec(j, i, 0, !type, ret);
				}
			}
			else {
				ll min_dif = INF, id_min = -1;
				for (int j : tree[i]) if (j != p) {
					ll at = solve(j, i, 1, !type) - solve(j, i, 0, !type);
					if (at < min_dif) {
						min_dif = at;
						id_min = j;
					}
				}
				for (int j : tree[i]) if (j != p) {
					if (j == id_min) rec(j, i, 1, !type, ret);
					else rec(j, i, 0, !type, ret);
				}
			}
		}
	}
	vector<vector<int>> go() {
		vector<vector<int>> ret;
		dp = vector(tree.size(), vector<ll>(2, -1));
		
		ll ans = solve(0, 0, 0, 0);
		//cout << "ans: " << ans << endl;
		if (ans >= INF) return ret;
		rec(0, 0, 0, 0, ret);
		return ret;
	}
};
 
int main() { _
	int n, m; cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b; a--, b--;
		g[a].push_back(b), g[b].push_back(a);
	}
	
	block_cut_tree T(g);
 
	auto ans = T.go();
	if (ans.empty()) return cout << -1 << endl, 0;
	cout << ans.size() << endl;
	for (auto v : ans) {
		cout << v.size() << " ";
		for (int i : v) cout << i+1 << " ";
		cout << endl;
	}
 
	exit(0);
}