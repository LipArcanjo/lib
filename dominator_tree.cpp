//implementaion from https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
//tested at problem https://codeforces.com/gym/102920/problem/F
//dominator tree is stored at tree[MAXN].

vector<int> g[MAXN],tree[MAXN],rg[MAXN],bucket[MAXN];
 
int sdom[MAXN],par[MAXN],dom[MAXN],dsu[MAXN],label[MAXN];
 
int arr[MAXN],rev[MAXN],T;
 
int find(int u, int x=0){
 
    if(u == dsu[u]) return x?-1:u;
 
    int v= find(dsu[u], x+1);
 
    if(v < 0){
        return u;
    }
 
    if( sdom[label[dsu[u]]] < sdom[label[u]] ){
        label[u] = label[dsu[u]];
    }
 
    dsu[u] = v;
 
    return x? v : label[u];
        
}
 
void uni(int u, int v){
    dsu[v] = u;
}
 
void dfs0(int u)
{
    T++;
    arr[u]=T;
    rev[T]=u;
    label[T]=T;
    sdom[T]=T;
    dsu[T]=T;
 
    for(int w : g[u]){
        if(!arr[w])
        {
            dfs0(w);
            par[arr[w]]=arr[u];
        }
        rg[arr[w]].pb(arr[u]);
    }
}
 
void dominator_tree(int source, int n){

    forn(i,n+1){
        rev[i] = -1;
    }

    T = 0;
    dfs0(source);

    for(int i = n; i >= 1; i--){
 
        if(rev[i] < 0  ) continue;
 
        for(int w : rg[i]){
            sdom[i] = min(sdom[i], sdom[find(w)]);
        }
 
        if(i > 1){
            bucket[sdom[i]].pb(i);
        }
 
        for(int w : bucket[i]){
            int v = find(w);
            if(sdom[v] == sdom[w]){
                dom[w] = sdom[w];
            }else{
                dom[w] = v;
            }
        }
 
        if(i > 1){
            uni(par[i], i);
        }
    }
 
    for(int i = 2; i <= n; i++){
 
        if(rev[i] < 0) continue;
 
        if(dom[i] != sdom[i]){
            dom[i] = dom[dom[i]];
        }
 
        tree[ rev[i] ].pb( rev[dom[i]] );
 
        tree[ rev[dom[i]] ].pb(rev[i]);
    }
 
}
