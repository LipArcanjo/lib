#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second
#define mset(a,b) memset(a, b, sizeof(a))
#define dbg(x) cout << "[" << #x << "]: " << x << endl;
#define forn(i,n) for(int i=0; i < n;i++)
#define each(val, v) for(auto val : v)
#define abs(u) (u >= 0 ? u : -u)

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vl = vector<ll>;

const int MAXN = 2e5 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;

ll gcd(ll a, ll b){
    if(b > a) swap(a,b);

    if(b == 0) return a;
    return gcd(b, a%b);
}

//this solution works in 2^k, where k is the number
// of primes that divide n

long long count(vl &a,
                int n, long long m)
{
    long long parity[3] = { 0 };
 
    for (int i = 1; i < (1 << n); i++) {
        long long mult = 1;
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
                mult *= a[j];
        //se a quantidade de bits ativados eh impar
        // soma-se na contagem, se nao, se subtrai.
        parity[__builtin_popcount(i) & 1]
            += (m / mult);
    }
 
    return parity[1] - parity[0];
}

ll cnt_relative(vl &primes, ll m){
    int n = primes.size();

    return m - count( primes, n, m );
}

ll cnt_relative_interval(ll n, ll l, ll r){


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

    ll ret = cnt_relative(primes, r);
    ret -= cnt_relative(primes, l-1);

    return ret;
}

//phi funciton, calcula the number of relative
//primes of n between [1, n-1]
ll cnt_relative_euler_totient(ll n){

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

    forn(i,sz){
        ans -= ans/primes[i];
    }
    return ans;
}


//aplied in a problem// https://codeforces.com/contest/1295/problem/D
void solve(){
    int t;
    cin >> t;
    while(t--){
        ll a,m;

        cin >> a >> m;

        ll g=  gcd(a,m);

        ll maxx = (a+m-1)/g;
        ll minn = (a)/g;
        
        ll n = m/g;

        ll ans = maxx - minn + 1;

        if(n == 1){
            cout << ans << endl;
            continue;
        }

        //ans = cnt_relative_interval( n, minn, maxx );
        ans = cnt_relative_euler_totient(n);

        cout << ans << endl;


    }
}

int main(){

    ios::sync_with_stdio(false); cin.tie(NULL);
    solve();

    return 0;
}