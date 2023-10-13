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
#define forn(i,n) for(int i=0; i < n;i++)

using ll = long long;
using db = long double; //pode ser double

using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<db,db>;

using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>; 
using vs = vector<string>;
using vpi = vector<pi>;
using vpl = vector<pl>; 
using vpd = vector<pd>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 2e6 + 5;
const int MOD = 1e9+7; //998244353;
const int INF = 0x3f3f3f3f;
const ll INF64 = ll(4e18) + 5;
const db EPS = 1e-9;
const db PI = acos((db)-1);



int add(int a, int b, int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

using D = ll;

struct Point{
	D x,y;
	Point(){
		x = 0;
		y = 0;
	}
	Point(D _x, D _y){
		x = _x;
		y = _y;
	}
	Point operator+(const Point &P) const{
		return Point(x + P.x, y + P.y);
	}
	Point operator/( const D &d) const{
		return Point( x/d, y/d);
	}
	Point operator-(const Point &P) const{
		return Point(x - P.x, y - P.y);
	}
	D operator^( const Point &P) const{
		return 1ll*x*P.y - 1ll*P.x*y;
	}
	bool operator< (const Point &P) const{
		if(x == P.x){
			return y < P.y;
		}
		return x < P.x;
	}
	bool operator> (const Point &P) const{
		if(x == P.x){
			return y > P.y;
		}
		return x > P.x;
	}
	bool operator==( const Point &P) const{
		pair<D,D> a1 = mp(x,y);
		pair<D,D> a2 = mp(P.x,P.y);
		return a1 == a2;
	}
	bool operator!=(const Point &P) const{
		return P.x != x || P.y != y;
	}
	bool operator <=(const Point&P) const{
		if(x == P.x) return y <= P.y;
		return x < P.x;
	}
	bool operator >=(const Point&P) const{
		if(x == P.x) return y >= P.y;
		return x > P.x;
	}
	pair<D,D> to_pair(){
		return mp(x,y);
	}
};

D cross(Point &A, Point &B, Point &C){
	Point d1 = C-A;
	Point d2 = C-B;
	return d1^d2;
}

Point C[MAXN];

int convex_hull(vector<Point> &P, int &ini_up){
	sort(P.begin(), P.end());
	int n = P.size();
	C[0] = P[0];
	int k = 1;
	for(int i = 1; i < n; i++){
		while( k >= 2 && cross(C[k-2], C[k-1], P[i]) < 0ll) k--;
		C[k++] = P[i];
	}
	ini_up = k-1;
	int ch = k + 1;
	for(int i = n-2; i >= 0; i--){
		while(k >= ch && cross(C[k-2], C[k-1], P[i]) < 0ll) k--;
		C[k++] = P[i];
	}
	return k;
}

int convex_hull1(vector<Point> &P, int &ini_up){
	int n = P.size();
	C[0] = P[0];
	int k = 1;
	for(int i = 1; i < n; i++){
		while( k >= 2 && cross(C[k-2], C[k-1], P[i]) <= 0ll) k--;
		C[k++] = P[i];
	}
	ini_up = k-1;
	int ch = k + 1;
	
	for(int i = n-2; i >= 0; i--){
		while(k >= ch && cross(C[k-2], C[k-1], P[i]) <= 0ll) k--;
		C[k++] = P[i];
	}
	return k;
}

//retorna indice do ponto mais proximo da coordenada x pela direita
int find_lower_hull(int ini_up, Point &P){
	int l = 0;
	int r = ini_up;
	while(l < r){
		int m = (l+r)/2;
		if(C[m].x >= P.x){
			r = m;
		}else{
			l = m+1;
		}
	}
	return r;
}

//retorna indice do ponto mais proximo da coordenada x pela esquerda
int find_upper_hull(int ini_up, int fim, Point &P){
	int l = ini_up;
	int r = fim;
	
	while(l < r){
		int m =(l+r)/2;
		if(C[m].x <= P.x){
			r = m;
		}else{
			l = m+1;
		}
	}
	return r;
}

bool inside_triang(Point &A, Point &B, Point &C, Point &D){
	ll a1 = (A-C)^(D-C);
	if(a1 <= 0ll) return false;
	return true;
}

Point mean(Point &A, Point &B){
	return (A+B)/2ll;
}

void solve(){
	int n;
	cin >> n;
	vector<Point> P(n, Point(0,0));

	forn(i,n){
		cin >> P[i].x;
		cin >> P[i].y;
		P[i].x *= 2;
		P[i].y *= 2;
	}

	vector<Point> F;

	int ini_up;
	int m = convex_hull(P, ini_up);
	
	set<pi> in_convex;
	forn(i,m-1){
		Point p = mean(C[i], C[i+1]);
		in_convex.insert(C[i].to_pair());
		F.pb(p);
	}
	int M1 = m-1;

	forn(i,n){
		pi p_at = P[i].to_pair();
		if(in_convex.find(p_at) != in_convex.end()) continue;
		vi id(2);
		id[0] = find_lower_hull(ini_up, P[i]);
		id[1] = find_upper_hull(ini_up, M1, P[i]);
		if(id[1] == M1) id[1] = 0;
		set<int> vis;
		forn(k,2){
			for(int b = -1; b <= 1; b++){
				int fim = add(id[k],b, M1);
				if(vis.find(fim) != vis.end()) continue;
				int ant = add(fim,-1, M1);
				int nxt = add(fim, 1, M1);
				vis.insert(fim);
				if( ( inside_triang(C[ant], C[fim], C[nxt], P[i]) )){
					Point p = mean(C[fim], P[i]);
					F.pb( p );	
				}
			}
		}
	}
	sort(F.begin(), F.end());
	int sz = F.size();
	int j = 0;
	forn(i, sz){
		if(i == 0 || !(F[i] == F[i-1])){
			F[j] = F[i];
			j++;
		}
	}
	F.resize(j);
	int ans = convex_hull1(F, ini_up) - 1;
	cout << ans << '\n';	
}

int main(){

	ios::sync_with_stdio(false); cin.tie(NULL);

	int t = 1;
	cin >> t;
	while(t--){
		solve();
	}

	return 0;
}

/*
   PRESTA ATENCAO!!!!

   NAO FIQUE PRESO EM UMA ABORDAGEM
   A SUA INTUICAO PODE ESTAR ERRADA - TENTE OUTRAS COISAS
   LIMPOU TUDO PARA O PROXIMO CASO?
   caso especial? n == 1 

 */
