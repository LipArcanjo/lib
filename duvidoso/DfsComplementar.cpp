#include<bits/stdc++.h>
using namespace std;
 
const int maxn=500007;

set<int> rv; // remained vertices
set<int> g[maxn]; // original graph
set<int> t[maxn]; // dfs tree
int deg[maxn];
int n,m;

// esta dfs funciona em (n+m)log(n)
void dfs(int u){
    rv.erase(u);
    int crt=0;
    while (1){
        auto iter=rv.upper_bound(crt);
        if (iter==rv.end()) break;
        int v=*iter;
        crt=v;
        if (g[u].find(v)!=g[u].end()) continue;
        t[u].insert(v), t[v].insert(u);
        dfs(v);
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int tc;
    cin>>tc;
    while (tc--){
        cin>>n>>m;
        for (int i=1;i<=n;++i) g[i].clear(), t[i].clear();
        rv.clear();
        for (int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            g[u].insert(v), g[v].insert(u);
        }
        for (int i=1;i<=n;++i) rv.insert(i);
        while (rv.size()>0){
            int u=*(rv.begin());
            dfs(u);       
        }
    }
}