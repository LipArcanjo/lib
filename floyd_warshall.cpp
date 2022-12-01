/*

*/

vpi g[MAXN];
int d[MAXN][MAXN];

void floyd_warshall(int n){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            d[i][j] = INF;
        }
    }


   
    for(int i = 0; i < n; i++){
	d[i][i] = 0;
        for(auto edge:g[i]){
            int v = edge.first;
            int w = edge.second;

            d[i][v] = w;
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(d[i][k] < INF && d[k][j] < INF){
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
}
