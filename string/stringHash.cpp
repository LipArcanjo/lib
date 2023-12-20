int add(int a, int b){
    a += b;
    if( a >= MOD) a -= MOD;
    if(a < 0) a += MOD;
    return a;
}
 
int mul(int a, int b){
    int ret = (1LL * a * b)%MOD;
    return ret;
}
 
int pw(int a, int n){
    int ret = 1;
    while(n > 0){
        if(n&1 == 1){
            ret = mul(ret, a);
        }
        a = mul(a,a);
        n = n>> 1;
    }
    return ret;
}
 
int inv(int a){
    return pw(a,MOD-2);
}
 
int gen_a(){
	int X = MOD/2;
	int L = rng();
	L %= MOD/4;
	if(L < 0) L += MOD/4;
	return X+L;
}

void process(int a, string &s, vector<int> &pwa, vector<int> &invpwa, vector<int> &sum){
	int n = s.size();
	pwa = invpwa = sum = vector<int>(n,0);
	pwa[0] = 1;
	invpwa[0] = 1;
	int inva = inv(a);
	for(int i = 1; i < n; i++){
		pwa[i] = mul(pwa[i-1],a);
		invpwa[i] = mul( invpwa[i-1],inva);
	}
	for(int i = 0; i < n; i++){
		sum[i] = add( mul(int(s[i]),pwa[i]), (i ? sum[i-1] : 0));
	}
}

int ghash(int i, int j, vector<int> &sum, vector<int> &invpwa){
	int h = add(sum[j], - (i ? sum[i-1] : 0));
	return mul(h, invpwa[i]);
}
