#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define int long long
void dbg_out() { cerr << endl; }
template <typename H, typename... T>
void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }
#define dbg(...) { cerr << #__VA_ARGS__ << ':'; dbg_out(__VA_ARGS__); }
#define all(x) x.begin(),x.end()
using ll = long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5;
const int MOD = 1e9+7; //998244353;
const int INF = 0x3f3f3f3f;
const ll INF64 = ll(4e18) + 5;

void solve(){
}

signed main(){

    ios::sync_with_stdio(false); cin.tie(NULL);

    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }

    return 0;
}

/*
Makefile:
CXXFLAGS=-Wall -Wextra -Wshadow -g -pedantic -fsanitize=address,undefined -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUGPEDANTIC -std=gnu++17
*/
