//cp algorithms

using T = long double;
const T EPS = 1E-9;

struct LineIntersection{

	struct pt {
		T x, y;
	};

	struct seg {
		pt p, q;
		int id;

		T get_y(T x) const {
			if (abs(p.x - q.x) < EPS)
				return p.y;
			return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
		}

		bool operator<(const seg& b) const
		{
			T x = max(min(p.x, q.x), min(b.p.x, b.q.x));
			return get_y(x) < b.get_y(x) - EPS;
		}
	};

	bool intersect1d(T l1, T r1, T l2, T r2) {
		if (l1 > r1)
			swap(l1, r1);
		if (l2 > r2)
			swap(l2, r2);
		return max(l1, l2) <= min(r1, r2) + EPS;
	}

	int vec(const pt& a, const pt& b, const pt& c) {
		T s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
		return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
	}

	bool intersect(const seg& a, const seg& b)
	{
		return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
			intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
			vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
			vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
	}

	struct event {
		T x;
		int tp, id;

		event() {}
		event(T x, int tp, int id) : x(x), tp(tp), id(id) {}

		bool operator<(const event& e) const {
			if (abs(x - e.x) > EPS)
				return x < e.x;
			return tp > e.tp;
		}
	};

	set<seg> s;
	vector<set<seg>::iterator> where;

	set<seg>::iterator prev(set<seg>::iterator it) {
		return it == s.begin() ? s.end() : --it;
	}

	set<seg>::iterator next(set<seg>::iterator it) {
		return ++it;
	}

	pair<int, int> get_an_intersection(const vector<seg>& a) {
		int n = (int)a.size();
		vector<event> e;
		for (int i = 0; i < n; ++i) {
			e.push_back(event(min(a[i].p.x, a[i].q.x), +1, i));
			e.push_back(event(max(a[i].p.x, a[i].q.x), -1, i));
		}
		sort(e.begin(), e.end());

		s.clear();
		where.resize(a.size());
		for (size_t i = 0; i < e.size(); ++i) {
			int id = e[i].id;
			if (e[i].tp == +1) {
				set<seg>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt);
				if (nxt != s.end() && intersect(*nxt, a[id]))
					return make_pair(nxt->id, id);
				if (prv != s.end() && intersect(*prv, a[id]))
					return make_pair(prv->id, id);
				where[id] = s.insert(nxt, a[id]);
			} else {
				set<seg>::iterator nxt = next(where[id]), prv = prev(where[id]);
				if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
					return make_pair(prv->id, nxt->id);
				s.erase(where[id]);
			}
		}

		return make_pair(-1, -1);
	}

	pair<int,int> get_an_intersection(vector<T> &x1, vector<T> &y1, vector<T> &x2, vector<T> &y2){
		int n = x1.size();
		vector<seg> a(n);
		for(int i = 0; i < n; i++){
			a[i].id = i;
			a[i].p.x = x1[i];
			a[i].p.y = y1[i];
			a[i].q.x = x2[i];
			a[i].q.y = y2[i];
		}
		return get_an_intersection(a);
	}

};
