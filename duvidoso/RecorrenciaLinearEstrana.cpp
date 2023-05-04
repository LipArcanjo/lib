#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif
 
#if 0
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>
 
    template<class T>
    using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update>;
#endif
 
#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <queue>
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <numeric> 
#include <complex>
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cstring>
#include <random>
#include <chrono>
#include <cassert>
 
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
 
#define each(a,x) for (auto& a: x)
#define tcT template<class T
#define tcTU tcT, class U
#define tcTUU tcT, class ...U
template<class T> using V = vector<T>; 
template<class T, size_t SZ> using AR = array<T,SZ>;
 
typedef string str;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
 
template<typename T, typename U> T &ctmax(T &x, const U &y){ return x = max<T>(x, y); }
template<typename T, typename U> T &ctmin(T &x, const U &y){ return x = min<T>(x, y); }
 
mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
 
#define ts to_string
str ts(char c) { return str(1,c); }
str ts(bool b) { return b ? "true" : "false"; }
str ts(const char* s) { return (str)s; }
str ts(str s) { return s; }
str ts(vector<bool> v) { str res = "{"; F0R(i,sz(v)) res += char('0'+v[i]);  res += "}"; return res; }
template<size_t SZ> str ts(bitset<SZ> b) { str res = ""; F0R(i,SZ) res += char('0'+b[i]); return res; }
template<class A, class B> str ts(pair<A,B> p);
template<class T> str ts(T v) { bool fst = 1; str res = "{"; for (const auto& x: v) {if (!fst) res += ", ";  fst = 0; res += ts(x);}  res += "}"; return res;}
template<class A, class B> str ts(pair<A,B> p) {return "("+ts(p.first)+", "+ts(p.second)+")"; }
 
template<class A> void pr(A x) { cout << ts(x); }
template<class H, class... T> void pr(const H& h, const T&... t) { pr(h); pr(t...); }
void ps() { pr("\n"); }
template<class H, class... T> void ps(const H& h, const T&... t) { pr(h); if (sizeof...(t)) pr(" "); ps(t...); }
 
void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {cerr << ts(h); if (sizeof...(t)) cerr << ", ";  DBG(t...); }
 
tcTU> void re(pair<T,U>& p);
tcT> void re(V<T>& v);
tcT, size_t SZ> void re(AR<T,SZ>& a);
 
tcT> void re(T& x) { cin >> x; }
void re(double& d) { str t; re(t); d = stod(t); }
void re(long double& d) { str t; re(t); d = stold(t); }
tcTUU> void re(T& t, U&... u) { re(t); re(u...); }
 
tcTU> void re(pair<T,U>& p) { re(p.first,p.second); }
tcT> void re(V<T>& x) { each(a,x) re(a); }
tcT, size_t SZ> void re(AR<T,SZ>& x) { each(a,x) re(a); }
tcT> void rv(int n, V<T>& x) { x.rsz(n); re(x); }
 
constexpr bool multitest();
void solve();
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t = 1;
  if (multitest()) cin >> t;
  for (; t; t--) solve();
}
 
 
 
 
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);  // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n); rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
  }
  vi rev(n);
  rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
      // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
      auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
      C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
      a[i + j + k] = a[i + j] - z;
      a[i + j] += z;
    }
}
 
typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  vl res(sz(a) + sz(b) - 1);
  int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
  vector<C> L(n), R(n), outs(n), outl(n);
  rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
  rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
  fft(L), fft(R);
  rep(i,0,n) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
  }
  fft(outl), fft(outs);
  rep(i,0,sz(res)) {
    ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
    ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
    res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
  }
  return res;
}
 
 
int MAX_D;
int K;
const int mod = 1000000000;
 
void linear_recurrence(vl& P, vl& Q, int n) {
  P.resize(MAX_D);
  Q.resize(MAX_D);
 
  for (; n; n >>= 1) {
    vl mQ = Q;
 
    for (int tk = 0; tk <= K; tk++) {
      for (int i = 1; i <= 10; i += 2) {
        if (mQ[tk*21+i]) mQ[tk*21 + i] = mod-mQ[tk*21 + i];
      }
    }
 
    vl U = convMod<mod>(P, mQ);
 
    for (int tk = 0; tk <= K; tk++) {
      for (int i = 0; i <= 10 && 2*i + (n&1) <= 20; i++) {
        P[tk*21 + i] = U[tk*21 + 2*i + (n&1)];
      }
    }
    
    if (n > 1) {
      vl A = convMod<mod>(Q, mQ);
      for (int tk = 0; tk <= K; tk++) {
        for (int i = 0; i <= 10; i++) {
          Q[tk*21 + i] = A[tk*21 + 2*i];
        }
      }
    }
  }
}
 
 
 
 
 
 
 
 
 
 
 
constexpr bool multitest() {return 0;}
 
void solve() {
  int n, m; re(n, m, K); n--;
 
  MAX_D = 21 * (K+1);
  vl P = {1};
  vl Q = {1};
  Q.resize(MAX_D);
 
  for (int i = 0; i < m; i++) {
    int d, p; re(d, p);
    if (Q[p*21+d]==0) Q[p*21+d]=mod;
    Q[p*21+d]--;
  }
 
  linear_recurrence(P, Q, n);
 
  ll t = 0;
  for (int i = 0; i <= K; i++) t += P[i*21];
 
  t %= mod;
  ps(t);
}
 
 
 
 
 
 
 