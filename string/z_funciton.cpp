
void z_function(vector<int> &z, string &s){
	int n = s.size();
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R-L] == s[R]) R++;
			z[i] = R-L; R--;
		} else {
			int k = i-L;
			if (z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R-L] == s[R]) R++;
				z[i] = R-L; R--;
			}
		}
	}
}
//// Achar pattern P em S -->
//// P#S

///z-functions -> z[i] eh o tamanho da maior substring de S que começa em
//s[i] e eh um prefixo de S.
