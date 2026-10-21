// 円環に並んだ n 個（n ≥ 2）を m 色で、隣り合う 2 個が異なる色になるように塗る方法の数を
// 998244353 で割った余りで求める。答えは (m-1)^n + (-1)^n (m-1)。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    long long n, m;
    cin >> n >> m;
    assert(2 <= n && 1 <= m);

    // --8<-- [start:core]
    // c[n] = （一列で両端が異なるもの）= m(m-1)^(n-1) - c[n-1] を解いた閉じた式
    mint ans = mint(m - 1).pow(n);
    if (n % 2 == 0) ans += mint(m - 1);
    else ans -= mint(m - 1);
    cout << ans.val() << '\n';
    // --8<-- [end:core]
}
