#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

void dbg_out() { cerr << endl; }
template <typename H, typename... T>
void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }
#define dbg(...) { cerr << #__VA_ARGS__ << ':'; dbg_out(__VA_ARGS__); }

using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vi = vector<int>;
using vl = vector<ll>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5;
const int MOD = 1e9+7; //998244353;
const int INF = 0x3f3f3f3f;
const ll INF64 = ll(4e18) + 5;

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod){
	u64 result = 1;
	base %= mod;
	while(e){
		if(e&1)
			result = (u128)result*base%mod;
		base = (u128)base*base%mod;
		e >>= 1;
	}
	return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s){
	u64 x = binpower(a,d,n);
	if(x == 1 || x ==  n-1)
		return false;
	for(int r = 1; r < s; r++){
		x = (u128)x*x%n;
		if(x == n-1)
			return false;
	}
	return true;
}

bool MillerRabin(u64 n){
	if(n < 2)
		return false;
	int r = 0;
	u64 d = n-1;
	while((d&1) == 0){
		d >>= 1;
		r++;
	}
	
	for(int a : {2,3,5,7,11,13,17,19,23,29,31,37}){
		if(n == a)
			return true;
		if(check_composite(n,a,d,r))
			return false;
	}
	return true;
}


void solve(){
}

int main(){

    ios::sync_with_stdio(false); cin.tie(NULL);

    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
