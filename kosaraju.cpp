/*
so garanto que compila

feito pelo fakhoury
*/


vi g[MAXN];
vi gr[MAXN];
int vis0[MAXN];
int vis1[MAXN];

int color[MAXN];
vi sameColor[MAXN];
vi scc[MAXN];
vi order;

void dfs0(int u){

    if(vis0[u]){
        return;
        
    }
    vis0[u] = 1;

    for(int v: g[u]){
        
        if(!vis0[v])
            dfs0(v);
    }

    order.pb(u);

}

void dfs1(int u, int col){
    if(vis1[u] ) return;

    vis1[u] = 1;

    for(int v : gr[u]){
        if(!vis1[v]) dfs1(v, col);
    }

    color[u] = col;
    sameColor[col].pb(u);
}

void kosaraju(int n){

    for(int i = 0; i < n; i++){
        if(!vis0[i]){
            dfs0(i);
        }
    }
	reverse(order.begin(), order.end());

    int cur_color = 0;

    for(int u : order){

        if(!vis1[u]){
            dfs1(u, ++cur_color);
        }

    }

    //build condensed graph
    for(int c = 1; c <= cur_color; c++ ){
        for(int u : sameColor[c]){
            for(int v : g[u]){
                if(color[v] != c)
                    scc[c].pb( color[v] );
            }
        }
    }

    for(int c = 1; c <= cur_color; c++){
        sort(scc[c].begin(), scc[c].end());

        scc[c].erase( unique(scc[c].begin(), scc[c].end()), scc[c].end() );
    }

}
