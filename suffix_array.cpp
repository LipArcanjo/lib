/*
made by turci
funciona

para mudar de string para vector<int>, troque os comentarios
*/
vector<int> build_suffix_array( string &s /*vector<int>&s*/  ) {
	s += '$';//s.pb(-INF);
	int n = s.size();
	vector<int> head(n), a(n), a1(n), c(n), c1(n);

	for(int i = 0; i < n; i++) a[i] = i;

	sort(a.begin(), a.end(), [&](int i, int j) {
		return s[i] < s[j];
	});

	int cc = 0;
    
	for(int i = 0; i < n; ++i) {
		if(i == 0 || s[a[i]] != s[a[i-1]]) {
			c[a[i]] = cc; 
			head[cc++] = i;
		} else{
            c[a[i]] = c[a[i-1]];
        } 
	}

	for(int l = 1; l < n; l *= 2) {

		for(int i = 0; i < n; i++) {
			int j = a[i] - l;
            if(j < 0) j += n;

			a1[head[c[j]]++] = j;
		}
		cc = 0;

		head.assign(head.size(), 0);
		for(int i = 0; i < n; i++) {

            int i_l = a1[i]+l;
            if(i_l >= n) i_l -= n;

            int j_l = a1[i-1]+l;
            if(j_l >= n) j_l -= n; 

			if(i == 0 || c[a1[i]] != c[a1[i-1]] || c[i_l] != c[j_l]) {
				head[cc] = i;
				c1[a1[i]] = cc++;
			} else c1[a1[i]] = c1[a1[i-1]];
		}

		a.assign(a1.begin(), a1.end());
		c.assign(c1.begin(), c1.end());

	}

    s.pop_back();
    a.erase( a.begin() );
    

	return a;
}

vector<int> build_lcp( string s /*vector<int> s*/, vector<int> p){

    int n = s.size();

    vector<int> rank(n,0);
    for(int i = 0; i < n; i++){
        rank[p[i]] = i;
    }

    int k = 0;
    vector<int> lcp(n-1,0);
    for(int i = 0; i < n; i++){
        if(rank[i] == n-1){
            k = 0;
            continue;
        }
        int j = p[rank[i]+1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]){
            k++;
        }
        lcp[rank[i]] = k;

        if(k) k--;            
    }

    return lcp;

}
