int primitive_root(int p){

    vector<int> fact;

    int phi = p-1,  n = phi;

    for(int i=2; i*i <=n; i++) if(n%i == 0){
        fact.pb(i);

        while(n%i == 0){
            n /= i;
        }
    }
    if(n > 1){
        fact.pb(n);
    }

    int szf = fact.size();

    for(int res = 2; res <= p; res++){
        bool ok = true;

        for(int i = 0; i < szf && ok; i++){
            ok &= pw(res, phi/fact[i]) != 1;
        }

        if(ok) return res;
    }

    return -1;
}

void ntt( vector<int> &a, ll n,  ll x , bool invert ){

    ll ctzll_n = __builtin_ctzll(n);
    for(int i = 0; i < n; i++){
        ll y = 0;
        for(int j = 0; j < ctzll_n; j++){
            if( (1LL << j)&i ){
                y |= ( 1LL << (ctzll_n - j - 1) );
            }
        }
        if(y > i){
            swap(a[i], a[y]);
        }
    }
     
    if(invert) x = inv(x);

    for(int s = 1; s < ctzll_n + 1; s++){
        int y = pw(x, (n/(1LL<<s)));
        int cur = (1LL << s);
        int pre = (1LL<<(s-1));

        for(int j = 0; j < n/cur; j++ ){
            int r = 1;
            for(int i = 0; i < pre ; i++  ){
                int u = a[i + j*cur];
                int v = mul( r,a[ i + j*cur + pre ]  );
                a[i+j*cur] = add(u,v);
                a[ i+j*cur + pre ] = add(u, -v);
                r = mul(r,y);
            }
        }
    }    

    if(invert){
        ll invn = inv(n);
        for(int i = 0; i < n; i++){
            a[i] = (a[i]*1LL*invn)%MOD;
        }
    }
    return;
}

void poly_multiplication( vector<int> &a, vector<int> &b, vector<int> &c, int p_root = 0){

    ll n = 1;

    ll sum_tam = ((ll)a.size()) + ((ll)b.size());

    
    while(n < sum_tam){

        n <<= 1;

    }

    vector<int> fa(a.begin(), a.end());
    fa.resize(n,0);

    vector<int> fb(b.begin(), b.end());
    fb.resize(n,0);

    ll x = pw(p_root, (MOD - 1)/n);


    ntt(fa,n, x, false);
    ntt(fb,n, x, false);

    c.resize(n,0);

    for(int i = 0; i < n; i++){
        c[i] = mul( fa[i], fb[i] );
    }
    ntt(c, n, x, true);

    c.resize( sum_tam - 1 , 0LL);

    return ;

}
