// 全体の平行移動を添字のずらしで表す
// 入力：N M K、続く M 行に追加の辺「x y」（x から y への有向辺。頂点は 1-indexed）
//       辺はほかに v → v+1（N → 1）の N 本がある
// 出力：頂点 1 から K 回移動する方法の数を 998244353 で割った余り
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 2 次元の表を 1 行ずつ作り直す素朴な方法（確かめ用。O((N + M) K)）
mint naive(int n, int k, const vector<int>& x, const vector<int>& y) {
    vector<mint> dp(n);
    dp[0] = 1;
    for (int t = 0; t < k; t++) {
        vector<mint> nx(n);
        for (int v = 0; v < n; v++) nx[(v + 1) % n] += dp[v];
        for (int j = 0; j < (int)x.size(); j++) nx[y[j]] += dp[x[j]];
        dp = nx;
    }
    mint s = 0;
    for (int v = 0; v < n; v++) s += dp[v];
    return s;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> x(m), y(m);
    for (int j = 0; j < m; j++) {
        cin >> x[j] >> y[j];
        x[j]--, y[j]--;
    }
    // --8<-- [start:core]
    // 時刻 t の本当の値は dp_t[v] = a[(v - t) mod n]。t を 1 増やすだけで全体が 1 つ右へずれる
    vector<mint> a(n);
    a[0] = 1;
    auto pos = [&](int v, int t) { return ((v - t) % n + n) % n; };
    vector<mint> add(m);
    for (int t = 0; t < k; t++) {
        for (int j = 0; j < m; j++) add[j] = a[pos(x[j], t)];  // 先に、ずらす前の値をすべて読む
        for (int j = 0; j < m; j++) a[pos(y[j], t + 1)] += add[j];  // 追加の辺の行き先だけ足す
    }
    mint ans = 0;
    for (int v = 0; v < n; v++) ans += a[v];
    // --8<-- [end:core]
    if ((long long)n * k <= 10000000) assert(ans == naive(n, k, x, y));
    cout << ans.val() << '\n';
}
