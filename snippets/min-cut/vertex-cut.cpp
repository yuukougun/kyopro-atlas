#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// 無向グラフで、頂点 0 から頂点 n - 1 へ行けなくするために消す頂点の費用の和の最小値と、
// 消す頂点を出力する。頂点 0 と n - 1 は消せない。消しても切り離せなければ -1 を出力する。
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> es(m);
    for (auto& [u, v] : es) cin >> u >> v;
    vector<long long> c(n);
    for (auto& x : c) cin >> x;
    // --8<-- [start:core]
    // 頂点 v の入口を 2v、出口を 2v + 1 とする
    long long inf = 1;
    for (int v = 1; v < n - 1; v++) inf += c[v];  // 有限の容量の総和より大きい
    atcoder::mf_graph<long long> g(2 * n);
    for (int v = 1; v < n - 1; v++) g.add_edge(2 * v, 2 * v + 1, c[v]);  // 消す費用
    for (auto [u, v] : es) {
        g.add_edge(2 * u + 1, 2 * v, inf);  // 辺は切れない
        g.add_edge(2 * v + 1, 2 * u, inf);  // 無向なので両向き
    }
    int s = 2 * 0 + 1, t = 2 * (n - 1);     // 始点は出口から、終点は入口まで
    long long cost = g.flow(s, t);
    vector<int> removed;
    if (cost < inf) {
        vector<bool> side = g.min_cut(s);
        for (int v = 1; v < n - 1; v++) {
            if (side[2 * v] && !side[2 * v + 1]) removed.push_back(v);  // 入口だけが s 側
        }
    }
    // --8<-- [end:core]
    if (cost >= inf) {
        cout << -1 << '\n';
        return 0;
    }
    long long sum = 0;
    for (int v : removed) sum += c[v];
    assert(sum == cost);
    cout << cost << '\n' << removed.size() << '\n';
    for (int v : removed) cout << v << '\n';
}
