//S is the first k terms and C is the coeficients
// use in the same order as // https://www.codechef.com/problems/RNG
// https://github.com/ShahjalalShohag/code-library/
// blob/main/Math/Linear%20Recurrence%20Fastest.cpp
int LinearRecurrence(vector<int>& S, vector<int> &C, long long n) {
  if (C.empty()) return 0;
  int k = (int)C.size();
  assert((int)S.size() == k);
  if (n < k) return S[n];
  auto Q = C;
  for (auto &x: Q) x = mod - x;
  Q.insert(Q.begin(), 1);
  auto P = multiply(S, Q); //poly multiplication
  P.resize(k);
  while(n) {
    auto Qminus = Q;
    for(int i = 1; i < (int)Qminus.size(); i += 2) Qminus[i] = mod - Qminus[i];
    auto S = multiply(P, Qminus); //poly multiplication
    auto T = multiply(Q, Qminus); //poly multiplication
    if(n & 1) {
      for(int i = 1 ; i < (int)S.size() ; i += 2) P[i>>1] = S[i];
      for(int i = 0 ; i < (int)T.size() ; i += 2) Q[i>>1] = T[i];
    } else {
      for(int i = 0 ; i < (int)S.size() ; i += 2) P[i>>1] = S[i];
      for(int i = 0 ; i < (int)T.size() ; i += 2) Q[i>>1] = T[i];
    }
    n >>= 1;
  }
  return P[0];
}