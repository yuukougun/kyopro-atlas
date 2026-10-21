// 併合の瞬間に寄与を数える：重み付きの木の全頂点対 (u, v)（u < v）について、
// パス上の最大の辺の重みの総和を求める。辺を重みの昇順に足し、併合のたびに
// 「重み × 両側の成分のサイズの積」を足す。
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<array<long long, 3>> edges(n - 1);  // {w, u, v}
    for (auto& [w, u, v] : edges) {
        cin >> u >> v >> w;
        assert(0 <= u && u < n && 0 <= v && v < n);
    }

    // --8<-- [start:core]
    sort(edges.begin(), edges.end());  // 重みの昇順
    atcoder::dsu d(n);
    long long ans = 0;
    for (auto [w, u, v] : edges) {
        // 併合する前に数える：このとき u 側・v 側の成分は w 以下の辺だけでできている
        long long su = d.size(u), sv = d.size(v);
        ans += w * su * sv;  // この su × sv 組のパスの最大は w に決まる
        d.merge(u, v);
    }
    // --8<-- [end:core]

    cout << ans << '\n';
}
