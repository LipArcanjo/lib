//from tfg: 
//https://github.com/tfg50/CompetitiveProgramming/
// matroid needs:
// add(object), reset(), check()

struct Edge {
	int u, v;
	Edge() {}
	Edge(int a, int b) : u(std::min(a, b)), v(std::max(a, b)) {}
};

class ChoiceMatroid {
public:
	ChoiceMatroid(const std::vector<int> &freq) : limit(freq) {}
	bool check(const Edge &e) { return cur[e.u] && cur[e.v]; }
	void add(const Edge &e) {
		assert(check(e));
		cur[e.u]--;
		cur[e.v]--;
	}
	void clear() {
		cur = limit;
	}
private:
	std::vector<int> limit, cur;
};

class GraphicMatroid {
public:
	GraphicMatroid(int n) : par(n, -1) {}
	bool check(const Edge &e) { return getPar(e.u) != getPar(e.v); }
	void add(const Edge &e) {
		assert(makeUnion(e.u, e.v));
	}
	void clear() {
		par.assign((int) par.size(), -1);
	}
private:
	std::vector<int> par;
	int getPar(int x) { return par[x] < 0 ? x : par[x] = getPar(par[x]); }

	bool makeUnion(int a, int b) {
		a = getPar(a), b = getPar(b);
		if(a == b) return false;
		if(par[a] < par[b]) std::swap(a, b);
		par[b] += par[a];
		par[a] = b;
		return true;
	}
};

// heavy matroid should be M1

template<class M1, class M2, class T>
class MatroidIntersection {
public:
	MatroidIntersection(M1 m1, M2 m2, const std::vector<T> &obj) {
		m1.clear();
		m2.clear();
		{
			// removing useless elements
			for(auto ob : obj) {
				if(m1.check(ob) && m2.check(ob)) {
					ground.push_back(ob);
				}
			}
			n = (int) ground.size();
			present.assign(n, false);
		}
		// greedy step
		for(int i = 0; i < n; i++) {
			if(m1.check(ground[i]) && m2.check(ground[i])) {
				present[i] = true;
				m1.add(ground[i]);
				m2.add(ground[i]);
			}
		}
		// augment step
		while(augment(m1, m2));
	}

	std::vector<T> getSet() {
		std::vector<T> ans;
		for(int i = 0; i < n; i++) {
			if(present[i]) {
				ans.push_back(ground[i]);
			}
		}
		return ans;
	}
private:
	int n;
	std::vector<T> ground;
	std::vector<int> curSet, dist;
	std::vector<bool> present;

	template<class M>
	void loadGround(M &m) {
		m.clear(), curSet.clear();
		for(int i = 0; i < n; i++) {
			if(present[i]) {
				m.add(ground[i]);
				curSet.push_back(i);
			}
		}
	}

	template<class M>
	int forwardEdge(int id, bool step, M &m) {
		assert(!present[id]);
		m.clear();
		m.add(ground[id]);
		for(auto i : curSet) {
			if(dist[i] != (step ? dist[id]-1 : -1)) {
				if(m.check(ground[i])) {
					m.add(ground[i]);
				}
			}
		}
		for(auto i : curSet) {
			if(dist[i] == (step ? dist[id]-1 : -1)) {
				if(m.check(ground[i])) {
					m.add(ground[i]);
				} else {
					return i;
				}
			}
		}
		return -1;
	}

	template<class M>
	int backwardEdge(int id, bool step, M &m) {
		assert(present[id]);
		m.clear();
		for(auto i : curSet) {
			if(i != id) {
				m.add(ground[i]);
			}
		}
		for(int i = 0; i < n; i++) {
			if(!present[i] && dist[i] == (step ? dist[id]-1 : -1)) {
				if(m.check(ground[i])) {
					return i;
				}
			}
		}
		return -1;
	}
 
	bool augment(M1 &m1, M2 &m2) {
		std::queue<int> q;
		dist.assign(n, -1);
		std::vector<int> frm(n, -1);
		loadGround(m1);
		for(int i = 0; i < n; i++) {
			if(!present[i] && m1.check(ground[i])) {
				q.push(i);
				dist[i] = 0;
			}
		}
		if(q.empty()) {
			return false;
		}
		auto getEdge = [&](int id, bool step) {
			if(!step) return dist[id] % 2 == 0 ? forwardEdge(id, step, m2) : backwardEdge(id, step, m1);
			else return dist[id] % 2 == 0 ? forwardEdge(id, step, m1) : backwardEdge(id, step, m2);
		};
		M2 checker2 = m2;
		loadGround(checker2);
		bool got = false;
		int limit = n + 1;
		while(!q.empty()) {
			int on = q.front();
			q.pop();
			if(dist[on] == limit) continue;
			for(int i = getEdge(on, false); i != -1; i = getEdge(on, false)) {
				q.push(i);
				dist[i] = dist[on] + 1;
				frm[i] = on;
				if(!present[i] && checker2.check(ground[i])) {
					got = true;
					limit = dist[i];
					/*for(int pos = i; pos != -1; pos = frm[pos]) {
						present[pos] = !present[pos];
					}
					return true;*/
				}
			}
		}
		if(!got) { return false; }
		M1 checker1 = m1;
		loadGround(checker1);
		std::function<bool(int)> dfs = [&](int on) {
			if(dist[on] == limit && !checker2.check(ground[on])) {
				dist[on] = -1;
				return false;
			}
			if(dist[on] == 0) {
				dist[on] = -1;
				if(checker1.check(ground[on])) {
					present[on] = !present[on];
					return true;
				} else {
					return false;
				}
			}
			for(int to = getEdge(on, true); to != -1; to = getEdge(on, true)) {
				assert(dist[to] == dist[on]-1);
				if(dfs(to)) {
					dist[on] = -1;
					present[on] = !present[on];
					return true;
				}
			}
			dist[on] = -1;
			return false;
		};
		got = false;
		for(int i = 0; i < n; i++) {
			if(dist[i] == limit && dfs(i)) {
				loadGround(checker1);
				loadGround(checker2);
				got = true;
			}
		}
		assert(got);
		return true;
	}
};
