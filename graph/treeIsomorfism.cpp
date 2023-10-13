
map<vector<int>,int> m;
int T=1;
 
struct Tree{
	vector<vector<int>> g;
	int n;
	vector<int> sz;
	vector<int> par;
	vector<int> cen;
	Tree(int _n): g(_n), n(_n),sz(_n),par(_n) {}
	
	void add_edge(int u, int v){
		g[u].pb(v);
		g[v].pb(u);
	}
	void dfs(int u, int p){
		sz[u] = 1;
		par[u] = p;
		for(auto v : g[u]) if(v != p){
			dfs(v,u);
			sz[u] += sz[v];
		}
	}
	
	void find_centroid(int u, int p){
		for(auto v : g[u]) if(v != p){
			find_centroid(v,u);
		}
		int maxx = 0;
		for(auto v : g[u]) if(v != p) maxx = max(maxx,sz[v]);
		if(u != p){
			maxx = max(n-sz[u],maxx);
		}
		if(maxx*2 <= n) cen.pb(u);
	}
	
	int hash(int u, int p){
		vector<int> s(1,0);
		for(auto v: g[u]) if(v != p){
			s.pb(hash(v,u));
		}
		sort(s.begin(), s.end());
		if(m.find(s) == m.end()) m[s] = T++;
		return m[s];
	}
 
	int hash(){
		dfs(0,0);
		find_centroid(0,0);
		vector<int> s;
		for(auto c : cen) s.pb(hash(c,c));
		sort(s.begin(), s.end());
		return s[0];
	}
};
 