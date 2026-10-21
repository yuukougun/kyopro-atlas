// 左 L 個・右 R 個の頂点の二部グラフで、端点を共有しない辺を k 本選ぶときの重みの和の最大を、k = 1, 2, … ごとに求める。
// 入力：L R N、続いて N 行の a b w（0-indexed。左の a と右の b を結ぶ重み w の辺。0 ≤ w ≤ 10^9）。
// 出力：1 行目に選べる本数の最大 K、続く K 行に k = 1, …, K の答え。
#include <bits/stdc++.h>
#include <atcoder/mincostflow>
using namespace std;

// --8<-- [start:core]
vector<long long> best_by_count(int l, int r, const vector<array<long long, 3>>& es) {
    const long long BIG = 1'000'000'000;  // 重みの最大以上。コスト BIG - w が 0 以上になる
    int s = l + r, t = l + r + 1;
    atcoder::mcf_graph<int, long long> g(l + r + 2);
    for (int i = 0; i < l; i++) g.add_edge(s, i, 1, 0);
    for (int j = 0; j < r; j++) g.add_edge(l + j, t, 1, 0);
    for (auto [a, b, w] : es) g.add_edge(a, l + b, 1, BIG - w);

    // 折れ線の頂点 (流量 x, 最小コスト g(x)) だけが返る。間の流量は直線で補う
    auto sl = g.slope(s, t);
    vector<long long> res;
    for (int i = 0; i + 1 < (int)sl.size(); i++) {
        auto [x0, c0] = sl[i];
        auto [x1, c1] = sl[i + 1];
        long long d = (c1 - c0) / (x1 - x0);  // この区間の 1 単位あたりのコスト（整数）
        for (int x = x0 + 1; x <= x1; x++) {
            long long cost = c0 + d * (x - x0);
            res.push_back(x * BIG - cost);  // 1 本ごとに足した BIG を戻す
        }
    }
    return res;
}
// --8<-- [end:core]

int main() {
    int l, r, n;
    cin >> l >> r >> n;
    vector<array<long long, 3>> es(n);
    for (auto& [a, b, w] : es) cin >> a >> b >> w;
    auto res = best_by_count(l, r, es);
    cout << res.size() << '\n';
    for (long long v : res) cout << v << '\n';
}
