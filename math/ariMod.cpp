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
        if(n&1){
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

int divide(int a, int b){
    return mul(a, inv(b));
}

int fat[MAXN+2];
int invfat[MAXN+2];

void pre_fat(int n){
	fat[0] = 1;
	fat[1] = 1;
	invfat[0] = 1;
	invfat[1] = 1;
	for(int i = 2; i <= n; i++){
		fat[i] = mul(fat[i-1], i);
	}
	invfat[n] = inv(fat[n]);
	for(int i = n-1; i >= 2; i--){
		invfat[i] = mul(invfat[i+1],i+1);
	}
}

int C(int n, int k){
    if(k > n) return 0;
    return mul( fat[n], mul( invfat[k], invfat[n-k] ) );
}
