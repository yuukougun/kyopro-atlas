#include <bits/stdc++.h>
using namespace std;

// 町 0..n-1、道は番号の小さい町から大きい町へだけ（u < v）。
// ある町で買い、そこから 1 本以上の道で行ける別の町で売るときの利益の最大。
// --8<-- [start:core]
long long max_profit(const vector<long long>& a, const vector<vector<int>>& to) {
    int n = a.size();
    const long long NEG = LLONG_MIN / 4;
    // best[u] ＝ u 自身を含め、u から行ける町の売値の最大
    vector<long long> best(n, NEG);
    long long ans = NEG;
    for (int u = n - 1; u >= 0; u--) {      // 行き先 v > u が先に確定している
        long long sell = NEG;               // u 以外で売るときの最高値
        for (int v : to[u]) sell = max(sell, best[v]);
        if (sell != NEG) ans = max(ans, sell - a[u]);
        best[u] = max(a[u], sell);          // 利益を出した後で u 自身を含める
    }
    return ans;                             // 負にもなりうる
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> to(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        assert(u < v);
        to[u].push_back(v);
    }
    cout << max_profit(a, to) << '\n';
}
