/*
li chao tree for MINIMUM VALUE
for MAXIMUN chanbe < to > in add_line function and min to max in get function

its possible to create it persistent if necessary
*/
typedef long long T;
typedef complex<T> point;
#define x real
#define y imag

T dot(point a, point b){
	return (conj(a)*b).x();
}

T f(point a, T x){
	return dot(a, {x,1});	
}

const int maxn = 2e5;

point line[4*MAXN];

void add_line(int r, int i, int j, point nw){
	int m = (i+j)/2;
	bool lef = f(nw,i) < f(line[r],i);
	bool mid = f(nw,m) < f(line[r],m);
	if(mid){
		swap(line[r],nw);
	}
	if(i == j){
		return;
	}
	if(lef != mid){
		add_line(2*r,l,m,nw);
	}else{
		add_line(2*r+1,m+1,j,nw);
	}
}

T get(int r, int i, int j, int x){
	int m = (l+r)/2;
	if(i == j) return f(line[r],x);
	if(x <= m) return min( f(line[r],x), get(2*r,i,m,x));
	return min( f(line[r],x), get(2*r+1,m+1,j,x));
}


