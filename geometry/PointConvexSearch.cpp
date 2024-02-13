
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
	Point d1 = B-A;
	Point d2 = C-A;
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
