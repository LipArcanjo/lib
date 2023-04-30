 const int N = 4e5;  // limit for array size
int nn;  // array size
int t[2 * N];
int vi[MAXN];


void build() {  // build the tree
  for (int i = nn - 1; i > 0; --i) t[i] = max(t[i<<1],t[i<<1|1]);
}

void build2(){
	for(int i = nn,j=1; i < 2*nn; i++,j++) t[i] = vi[j];
	build();
}

void modify(int p, int value) {  // set value at position p
  p--;
  for (t[p += nn] = value; p > 1; p >>= 1) t[p>>1] = max(t[p],t[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  l--;
  for (l += nn, r += nn; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res,t[l++]);
    if (r&1) res = max(res,t[--r]);
  }
  return res;
}
 
vector<int> g[MAXN];
 
int sz[MAXN];
int id[MAXN];
int par[MAXN];
int h[MAXN];
int T = 1;
void dfs0(int u, int p){
	int tam = g[u].size();
	par[u] = p;
	sz[u] = 1;
	for(int i = 0; i < tam; i++) if(g[u][i] != p){
		int v = g[u][i];
		dfs0(v,u);
		sz[u] += sz[v];
		if( sz[g[u][i]] > sz[g[u][0]] || g[u][0] == p) swap(g[u][i],g[u][0]);
	}
}
 
void dfs1(int u, int p, int root){
	id[u] = T++;
	h[u] = root;
	for(auto v : g[u]) if(v != p){
		dfs1(v,u, (g[u][0] == v ? root : v));
	}
}
 
void mount_hld(int root, vector<int> a, int n){
	dfs0(root,root);
	dfs1(root,root,root);
	for(int i = 1; i <= n; i++){
		vi[id[i]] = a[i];
	}
	build2();
}
 
void update_hld(int i, int v, int n){
	modify(id[i],v);
}


int query_hld(int a, int b, int n){
	if(a == b){
		return query(id[a],id[a]);
	}
	if(id[a] < id[b]) swap(a,b);

	if(h[a] == h[b]) return query(id[b],id[a]);
	return max( query(id[h[a]],id[a]), query_hld(par[h[a]], b, n));
}