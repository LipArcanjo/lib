//mobius transform, u(f(s)) = sum t in s (-1)^|t\t|f(t)
// https://codeforces.com/blog/entry/72488
for(int i = 0; i < N; i++) {
    for(int mask = 0; mask < (1 << N); mask++) {
        if((mask & (1 << i)) != 0) {
            f[mask] -= f[mask ^ (1 << i)]
        }
    }
}
for(int mask = 0; mask < (1 << N); mask++)  zinv[mask] = mu[mask] = f[mask]