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

//point
typedef double T;
struct pt{
	T x,y;
	pt operator+(pt p) {return {x+p.x,y+p.y};}
	pt operator-(pt p) {return {x-p.x,y-p.y};}
	pt operator*(T d) {return {x*d, y*d};}
	pt operator/(T d) {return {x/d, y/d};} //only for floating point
};

bool operator==(pt a, pt b) {return a.x == b.x && a.y == b.y;}
bool operator!=(pt a, pt b) {return !(a==b);}
bool operator<(pt a, pt b) {return a.x < b.x || (a.x == b.x && a.y < b.y);}


T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}

ostream& operator<<(ostream& os, pt p){
	return os << "(" << p.x << "," << p.y << ")";
}

template<typename T> int sgn(T x){
	return (T(0) < x) - (x < T(0));
}

pt translate(pt v, pt p) {return p+v;}
pt scale(pt c, double factor, pt p){
	return c + (p-c)*factor;
}
pt rot(pt p, double a){
	return{p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
}
pt perp(pt p) {return {-p.y,p.x};}

T dot(pt v, pt w) {return v.x*w.x + v.y+w.y;}
T cross(pt v, pt w) {return v.x*w.y - v.y+w.x;}

bool isPerp(pt v, pt w) {return dot(v,w) == 0;}

double angle(pt v, pt w){
	double cosTheta = dot(v,w) / abs(v) / abs(w);
	return acos(max(-1.0,min(1.0,cosTheta)));
}

T orient(pt a, pt b, pt c) {return cross(b-a,c-a);}

bool inAngle(pt a, pt b, pt c, pt p){
	assert(orient(a,b,c) != 0);
	if(orient(a,b,c) < 0) swap(b,c);
	return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

double orientedAngle(pt a, pt b, pt c){
	if(orient(a,b,c) >= 0)
		return angle(b-a,c-a);
	else
		return 2*M_PI - angle(b-a,c-a);
}

bool half(pt p){
	return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSortAround(pt o, vector<pt> &v){
	sort(v.begin(), v.end(), [&](pt v, pt w){
		return make_tuple(half(v-o),0) < 
			make_tuple(half(w-o), cross(v-o,w-o));
	});
}
//line
struct line{
	pt v; T c;
	line(pt v, T c) : v(v), c(c) {}
	line(T a, T b, T c): v({b,-a}), c(c) {}
	line(pt p, pt q): v(q-p), c(cross(v,p)) {}

	T side(pt p) {return cross(v,p)-c;}
	double dist(pt p) {return abs(side(p))/abs(v);}
	double sqDist(pt p) {return side(p)*side(p)/(double)sq(v);}
	line perpThrough(pt p) {return {p, p+perp(v)};}
	bool cmpProj(pt p, pt q){ //not sure if its right
		return dot(v,p) < dot(v,q);
	}
	line translate(pt t) {return {v, c+cross(v,t)};}
	line shiftLeft(double dist) {return {v, c+dist*abs(v)};}
	pt proj(pt p) {return p - perp(v)*side(p)/sq(v);}
	pt refl(pt p) {return p - perp(v)*2*side(p)/sq(v);}
};

bool inter(line l1, line l2, pt &out){
	T d = cross(l1.v, l2.v);
	if(d == 0) return false;
	out = (l2.v*l1.c - l1.v*l2.c)/d;
	return true;
}

line bisector(line l1, line l2, bool interior){
	assert(cross(l1.v, l2.v) != 0);
	double sign = interior ? 1 : -1;
	return {l2.v/abs(l2.v) + l1.v/abs(l1.v)*sign,
			l2.c/abs(l2.v) + l1.c/abs(l1.v)*sign};
}
//segment
bool inDisk(pt a, pt b, pt p){
	return dot(a-p,b-p) <= 0;
}

bool onSegment(pt a, pt b, pt p){
	return orient(a,b,p) == 0 && inDisk(a,b,p);
}

bool properInter(pt a, pt b, pt c, pt d, pt &out){
	double oa = orient(c,d,a),
		   ob = orient(c,d,b),
		   oc = orient(a,b,c),
		   od = orient(a,b,d);
	if(oa*ob < 0 && oc*od < 0){
		out = (a*ob - b*oa)/(ob-oa);
		return true;
	}
	return false;
}

set<pt> inters(pt a, pt b, pt c, pt d){
	pt out;
	if(properInter(a,b,c,d,out)) return {out};
	set<pt> s;
	if(onSegment(c,d,a)) s.insert(a);
	if(onSegment(c,b,d)) s.insert(b);
	if(onSegment(a,b,c)) s.insert(c);
	if(onSegment(a,b,d)) s.insert(d);
	return s;
}

double segPoint(pt a, pt b, pt p){
	if(a != b){
		line l(a,b);
		if(l.cmpProj(a,p) && l.cmpProj(p,b))
			return l.dist(p);
	}
	return min(abs(p-a),abs(p-b));
}

double segSeg(pt a, pt b, pt c, pt d){
	pt dummy;
	if(properInter(a,b,c,d,dummy))
		return 0;
	return min({segPoint(a,b,c), segPoint(a,b,d),
				segPoint(c,d,a), segPoint(c,d,b)});
}
//poly
double areaTriangle(pt a, pt b, pt c){
	return abs(cross(b-a,c-a))/2.0;
}

double areaPolygon(vector<pt> p){
	double area = 0.0;
	for(int i = 0; n=p.size(); i < n; i++){
		area += cross(p[i],p[(i+1)%n]);
	}
	return abs(area)/2.0;
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
