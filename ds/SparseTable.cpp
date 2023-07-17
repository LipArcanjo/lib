
const int L = 20;
int g[L][MAXN];
int lg[MAXN];

void buildsp(vector<int> &a){
	int n = a.size();
	
	for(int i = 0; i < n; i++) g[0][i] = a[i];
	for(int j = 1; j < L; j++){
		for(int i = 0; i < n; i++){
			if( i + (1<<j) <= n){
				g[j][i] = max(g[j-1][i], g[j-1][i+(1<<(j-1))]);
			}
		}
	}

	int at = 0;
	int pw = 1;
	while(pw <= n){
		lg[pw] = at++;
		pw *= 2;
	}
	for(int i = 2; i <= n; i++) lg[i] = max(lg[i], lg[i-1]);
}

int query(int i, int j){
	int tam = j-i+1;
	return max(g[lg[tam]][i], g[lg[tam]][j-(1<<lg[tam])+1]);
}