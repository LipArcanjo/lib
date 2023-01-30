#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
 
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cout << "[" << #x << "]: " << x << endl;
 
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
 
int gera_a(){
	int X = MOD/2;
	int L = rng();
	L %= MOD/4;
	if(L < 0) L += MOD/4;
	return X+L;
}
 
void solve(){
	string s;
	cin >> s;
	int n = s.size();
	int a = gera_a();
	vi pwa(n);
	vi invpwa(n);
	int inva = inv(a);
	pwa[0] = 1;
	invpwa[0] = 1;
	for(int i = 1; i < n; i++){
		pwa[i] = mul(pwa[i-1],a);
		invpwa[i] = mul(invpwa[i-1],inva);
	}
	vi sum(n);
	for(int i = 0; i < n; i++){
		sum[i] = add( mul(int(s[i]),pwa[i]), (i ? sum[i-1] : 0));
	}
 
	auto ghash = [&](int a, int b){
		int h = add(sum[b] ,- (a ? sum[a-1] : 0));
		return mul(h, invpwa[a]);
	};
	int ans = 0;
	for(int len = 1; len < n; len++){
		int hash1 = ghash(0,len-1);
		int hash2 = ghash(n-len, n-1);
		if(hash1 == hash2) cout << len << ' ';
	}cout << '\n';
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