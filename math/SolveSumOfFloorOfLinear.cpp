//nao faco ideia como funciona
//https://github.com/yosupo06/library-checker-problems/blob/master/math/sum_of_floor_of_linear/sol/correct.cpp
/**
 * a / b, a // b : 小数, 整数としての割り算
 * sum_{i = 0..n-1} floor((ai + b) // m) を求める
 * 
 * 線分 y = (ax + b) / m, (0 <= x <= n)は真下に何個(完全な)正方形を含むか？と同値
 */
ll sum_of_floor(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    /**
     * 線分の端点を、y座標が整数になるようにちょっとずらす -> 90度回転
     * y座標: (b / m, (an + b) / m) -> (0, y_max)
     * x座標: (0, n) -> (-b / a, x_max / a)
     * 
     * 端点をずらすことで答えは (n - ceil(x_max / a)) * y_max 減る
     * 
     * 90度回転する
     * (m / a) * x + (b2 / a) = y_max
     */

    ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += sum_of_floor(y_max, a, m, (a - x_max % a) % a);
    return ans;
}