// 密なグラフ（完全グラフ）の最小全域木を、配列を使うプリム法で O(N^2) で求める
// 入力：N、続く N 行は点の座標「x y」。2 点の間の辺の重みをマンハッタン距離とする
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
// 完全グラフの最小全域木の重みの和。cost(i, j) は辺 (i, j) の重みを返す関数
template <class F>
long long prim_dense(int n, F cost) {
    const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ
    vector<long long> mind(n, INF);  // mind[v]：木の頂点から v への辺の重みの最小
    vector<bool> in_tree(n, false);
    mind[0] = 0;  // 頂点 0 から木を伸ばす
    long long total = 0;
    for (int step = 0; step < n; step++) {
        int v = -1;  // 木の外で mind が最小の頂点
        for (int i = 0; i < n; i++) {
            if (!in_tree[i] && (v == -1 || mind[i] < mind[v])) v = i;
        }
        in_tree[v] = true;
        total += mind[v];
        for (int i = 0; i < n; i++) {  // v から出る辺で mind を更新する
            if (!in_tree[i]) mind[i] = min(mind[i], cost(v, i));
        }
    }
    return total;
}
// --8<-- [end:core]

// 確かめ用：全辺を並べてクラスカル法で求める
long long kruskal_all(int n, const function<long long(int, int)>& cost) {
    vector<tuple<long long, int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) edges.emplace_back(cost(i, j), i, j);
    }
    sort(edges.begin(), edges.end());
    atcoder::dsu d(n);
    long long total = 0;
    for (const auto& [w, u, v] : edges) {
        if (!d.same(u, v)) {
            d.merge(u, v);
            total += w;
        }
    }
    return total;
}

int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    auto cost = [&](int i, int j) { return llabs(x[i] - x[j]) + llabs(y[i] - y[j]); };
    long long ans = prim_dense(n, cost);
    assert(ans == kruskal_all(n, cost));
    cout << ans << '\n';
}
