#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// 一般のグラフで「各辺 uv で x_u + x_v <= 1、0 <= x_v <= 1」の下での
// x の総和の最大（最大独立集合の LP 緩和）を、頂点を 2 倍にした二部グラフで求める。
// 戻り値は 2 倍した値 y_v = 2 x_v（0・1・2 のどれか）と、その総和
// --8<-- [start:core]
pair<int, vector<int>> lp_independent_set(int n, const vector<pair<int, int>>& edges) {
    // 左の頂点 v は v、右の頂点 v は n + v
    int s = 2 * n, t = s + 1;
    atcoder::mf_graph<int> g(2 * n + 2);
    for (int v = 0; v < n; v++) {
        g.add_edge(s, v, 1);
        g.add_edge(n + v, t, 1);
    }
    for (auto [u, v] : edges) {  // 辺 uv を u左–v右 と v左–u右 の 2 本にする
        g.add_edge(u, n + v, 1);
        g.add_edge(v, n + u, 1);
    }
    int nu = g.flow(s, t);
    vector<bool> reach = g.min_cut(s);
    vector<int> y(n);
    for (int v = 0; v < n; v++) {
        y[v] = (reach[v] ? 1 : 0) + (reach[n + v] ? 0 : 1);  // 独立集合に入る数
    }
    return {2 * n - nu, y};  // 総和は 2 倍した二部グラフの最大独立集合の大きさ
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) cin >> u >> v;

    auto [total, y] = lp_independent_set(n, edges);
    assert(accumulate(y.begin(), y.end(), 0) == total);
    for (auto [u, v] : edges) assert(y[u] + y[v] <= 2);  // x_u + x_v <= 1

    // 小さいグラフで、半整数の解 y ∈ {0, 1, 2}^n を全探索して比べる
    if (n <= 8) {
        int best = 0, pw = 1;
        for (int i = 0; i < n; i++) pw *= 3;
        for (int code = 0; code < pw; code++) {
            vector<int> z(n);
            for (int i = 0, c = code; i < n; i++, c /= 3) z[i] = c % 3;
            bool ok = true;
            for (auto [u, v] : edges) ok = ok && z[u] + z[v] <= 2;
            if (ok) best = max(best, accumulate(z.begin(), z.end(), 0));
        }
        assert(best == total);
    }

    cout << total << '\n';
    for (int v = 0; v < n; v++) cout << y[v] << (v + 1 < n ? ' ' : '\n');
}
