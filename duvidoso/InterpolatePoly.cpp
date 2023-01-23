#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int add(int x, int y)
{
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}

int mul(int x, int y)
{
    return (x * 1ll * y) % MOD;
}

int binpow(int x, int y)
{
    int z = 1;
    while(y)
    {
        if(y & 1) z = mul(z, x);
        x = mul(x, x);
        y >>= 1;
    }
    return z;
}

int inv(int x)
{
    return binpow(x, MOD - 2);
}

int divide(int x, int y)
{
    return mul(x, inv(y));
}

typedef vector<int> poly;

void norm(poly& p)
{
    while(p.size() > 0 && p.back() == 0)
        p.pop_back();
}

poly operator +(const poly& a, const poly& b)
{
    poly c = a;
    while(c.size() < b.size()) c.push_back(0);
    for(int i = 0; i < b.size(); i++) c[i] = add(c[i], b[i]);
    norm(c);
    return c;
}

poly operator +(const poly& a, int b)
{
    return a + poly(1, b);
}

poly operator +(int a, const poly& b)
{
    return b + a;
}

poly operator *(const poly& a, int b)
{
    poly c = a;                               
    for(int i = 0; i < c.size(); i++) c[i] = mul(c[i], b);
    norm(c);
    return c;
}

poly operator /(const poly& a, int b)
{   
    return a * inv(b);
}

poly operator *(const poly& a, const poly& b)
{
    poly c(a.size() + b.size() - 1);
    for(int i = 0; i < a.size(); i++)
        for(int j = 0; j < b.size(); j++)
            c[i + j] = add(c[i + j], mul(a[i], b[j]));

    norm(c);
    return c;
}

poly interpolate(const vector<int>& x, const vector<int>& y)
{
    int n = int(x.size()) - 1;
    vector<vector<int> > f(n + 1);
    f[0] = y;
    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= n - i; j++)
            f[i].push_back(divide(add(f[i - 1][j + 1], -f[i - 1][j]), add(x[i + j], -x[j])));
    
    poly cur = poly(1, 1);
    poly res;
    for(int i = 0; i <= n; i++)
    {
        res = res + cur * f[i][0];
        cur = cur * poly({add(0, -x[i]), 1});
    }

    return res;
}

int eval(const poly& a, int x)
{
    int res = 0;
    for(int i = int(a.size()) - 1; i >= 0; i--)
        res = add(mul(res, x), a[i]);
    return res;
}

poly sumFromL(const poly& a, int L, int n)
{
    vector<int> x;
    for(int i = 0; i <= n; i++)
        x.push_back(L + i);
    vector<int> y;
    int cur = 0;
    for(int i = 0; i <= n; i++)
    {
        cur = add(cur, eval(a, x[i]));
        y.push_back(cur);
    }
    return interpolate(x, y);
}

int sumOverSegment(const poly& a, int L, int R)
{
    return eval(sumFromL(a, L, a.size()), R - 1);
}

int main() {
    int n;
    cin >> n;
    vector<int> L(n), R(n);
    for(int i = 0; i < n; i++)
    {
        cin >> L[i] >> R[i];
        R[i]++;
    }
    reverse(L.begin(), L.end());
    reverse(R.begin(), R.end());

    vector<int> coord = {0, MOD - 1};
    for(int i = 0; i < n; i++)
    {
        coord.push_back(L[i]);
        coord.push_back(R[i]);
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    vector<int> cL = coord, cR = coord;
    cL.pop_back();
    cR.erase(cR.begin());
    int cnt = coord.size() - 1;
    vector<poly> cur(cnt);
    for(int i = 0; i < cnt; i++)
        if(cL[i] >= L[0] && cR[i] <= R[0])
            cur[i] = poly(1, inv(R[0] - L[0]));
    for(int i = 1; i < n; i++)
    {
        vector<poly> nxt(cnt);        
        int curSum = 0;
        for(int j = 0; j < cnt; j++)
        {
            nxt[j] = sumFromL(cur[j], cL[j], i) + curSum;
            curSum = add(curSum, sumOverSegment(cur[j], cL[j], cR[j]));    
        }
        for(int j = 0; j < cnt; j++)
            nxt[j] = nxt[j] * (cL[j] >= L[i] && cR[j] <= R[i] ? inv(R[i] - L[i]) : 0);
        cur = nxt;
    }
    int ans = 0;
    for(int i = 0; i < cnt; i++)
        ans = add(ans, sumOverSegment(cur[i], cL[i], cR[i]));

    cout << ans << endl;
}