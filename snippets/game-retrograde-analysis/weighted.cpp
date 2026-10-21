// 得点のあるゲーム：有向グラフの頂点に駒があり、先手（min）と後手（max）が交互に辺に沿って動かす。
// 動かせなくなったら終わり、得点は通った辺の重み（非負）の和。
// min の人は有限で終わらせたうえで得点を小さく、max の人は終わらせないか、無理なら得点を大きくしたい。
// 各頂点 v について、v に駒があり min の人の手番の局面の値を出す（終わらないなら INF）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> rev(n);  // 逆辺 (移る前の頂点, 重み)
    vector<int> cnt(n, 0);                        // max の局面で、値が確定していない行き先の数
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        assert(w >= 0);
        rev[v].push_back({u, w});
        cnt[u]++;
    }

    // --8<-- [start:core]
    // 局面 (v, t)：t = 0 は min の人の手番、t = 1 は max の人の手番
    const long long INF = LLONG_MAX;
    vector<array<long long, 2>> val(n, {INF, 0});  // 確定した値（max の局面は候補の最大値）
    vector<array<bool, 2>> done(n, {false, false});
    // (値, 頂点, 手番) を値の小さい順に取り出す
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
    for (int v = 0; v < n; v++) {
        if (cnt[v] == 0) {  // 動けない局面は値 0 で確定
            pq.push({0, v, 0});
            pq.push({0, v, 1});
        }
    }
    while (!pq.empty()) {
        auto [x, v, t] = pq.top();
        pq.pop();
        if (done[v][t]) continue;
        done[v][t] = true;
        val[v][t] = x;
        for (auto [u, w] : rev[v]) {
            if (t == 1) {
                // u は min の局面：候補を積む。最初に取り出された候補が最小で確定する
                if (!done[u][0]) pq.push({x + w, u, 0});
            } else {
                // u は max の局面：行き先がすべて確定したら、候補の最大値で確定する
                val[u][1] = max(val[u][1], x + w);
                if (--cnt[u] == 0) pq.push({val[u][1], u, 1});
            }
        }
    }
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) {
        if (v > 0) cout << ' ';
        if (done[v][0]) {
            cout << val[v][0];
        } else {
            cout << "INF";
        }
    }
    cout << '\n';
}
