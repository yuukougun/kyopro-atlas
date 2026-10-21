// 重み付きの木で、パス上の辺の重みの XOR がちょうど X になる頂点の組 {u, v}（u ≠ v）を数える
// 入力：N X、続く N - 1 行に辺 u v w（1-indexed）
// 出力：組の数
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    // --8<-- [start:core]
    // S[v] = 根 0 から v までの辺の重みの XOR（BFS 順で親から子へ配る）
    vector<long long> S(n, 0);
    vector<int> par(n, -1), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (auto [c, w] : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            S[c] = S[v] ^ w;
            order.push_back(c);
        }
    }
    // u と v の間の XOR は S[u] ^ S[v]。すでに見た頂点の S の個数を数えておき、
    // 自分と組になる値 S[v] ^ x の個数を足す（自分自身と、同じ組の 2 回目は数えない）
    map<long long, long long> cnt;
    long long ans = 0;
    for (int v = 0; v < n; v++) {
        auto it = cnt.find(S[v] ^ x);
        if (it != cnt.end()) ans += it->second;
        cnt[S[v]]++;
    }
    // --8<-- [end:core]
    assert(ans <= (long long)n * (n - 1) / 2);
    cout << ans << '\n';
}
