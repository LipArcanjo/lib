/*
so garanto que compila

cp-algorithms
*/

vector<pair<int,int>> g[MAXN];

bool SPFA(int n, int v0, vector<int> &d, vector<int> &p){
	d.assign(n,INF);
	d[v0] = 0;
	vector<bool> inq(n,false);
	vector<int> cnt(n,0);
	queue<int> q;
	q.push(v0);	
	p.assign(n,-1);

	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;

		for(auto edge: g[u]){
			int v = edge.first;
			int w = edge.second;

			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				p[v] = u;
				
				if(!inq[v]){
					inq[v] = true;
					q.push(v);
					cnt[v]++;

					if(cnt[v] > n){
						return false;
					}
				}
			}
		}
	}
	return true;
}
