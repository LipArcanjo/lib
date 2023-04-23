/*
    phi - euler_totient_function
    calcula a quantidade de numeros no intervalo
    [1,n] que eh coprimo com n.
*/
ll phi(ll n){

    vl primes;
    ll nn = n;
    for(ll i = 2; i*i <= nn; i++){
        if(nn%i == 0){
            primes.pb(i);

            while( nn%i == 0 ){
                nn /= i;
            }
        }
    }
    if(nn > 1){
        primes.pb(nn);
    }

    int sz = primes.size();

    ll ans = n;
    for(int i = 0; i < sz; i++){
        ans -= ans/primes[i];
    }
    return ans;
}