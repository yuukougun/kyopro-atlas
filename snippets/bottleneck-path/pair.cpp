#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
// s から t への経路の「辺の重みの最大値」の最小値。つながらなければ -1
long long bottleneck(int n, vector<array<long long, 3>> edges, int s, int t) {
    if (s == t) return 0;  // 辺を 1 本も通らない
    sort(edges.begin(), edges.end(),
         [](const auto& a, const auto& b) { return a[2] < b[2]; });
    atcoder::dsu d(n);
    for (auto [u, v, w] : edges) {
        d.merge(u, v);
        if (d.same(s, t)) return w;  // 初めてつながった辺の重みが答え
    }
    return -1;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> edges(m);
    for (auto& [u, v, w] : edges) cin >> u >> v >> w;
    int s, t;
    cin >> s >> t;
    cout << bottleneck(n, edges, s, t) << '\n';
}
