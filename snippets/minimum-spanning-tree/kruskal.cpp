// クラスカル法で最小全域木の重みを求める（連結でなければ -1）
// 入力：N M、続く M 行は「u v w」（0-indexed の頂点 u・v を重み w の無向辺で結ぶ）
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
struct Edge {
    long long w;
    int u, v;
};

// 最小全域木の重みの和を返す。グラフが連結でなければ -1 を返す
long long kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    atcoder::dsu d(n);
    long long total = 0;
    int used = 0;  // 採用した辺の本数
    for (const auto& [w, u, v] : edges) {
        if (d.same(u, v)) continue;  // 両端がすでに連結：採ると閉路になるので捨てる
        d.merge(u, v);
        total += w;
        used++;
        if (used == n - 1) break;  // 全域木が完成した
    }
    return used == n - 1 ? total : -1;
}
// --8<-- [end:core]

// 素朴な方法：N - 1 本の辺の選び方をすべて試し、連結になるものの重みの最小を求める
long long brute(int n, const vector<Edge>& edges) {
    int m = edges.size();
    long long best = -1;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        atcoder::dsu d(n);
        long long sum = 0;
        for (int i = 0; i < m; i++) {
            if (mask >> i & 1) {
                d.merge(edges[i].u, edges[i].v);
                sum += edges[i].w;
            }
        }
        if ((int)d.groups().size() == 1 && (best == -1 || sum < best)) best = sum;
    }
    return best;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (auto& [w, u, v] : edges) cin >> u >> v >> w;
    long long ans = kruskal(n, edges);
    if (m <= 16) assert(ans == brute(n, edges));
    cout << ans << '\n';
}
