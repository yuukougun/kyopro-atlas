// 辺の値を子の頂点に寄せる：根から BFS して親を決め、辺 (par[c], c) の重みを val[c] に置く
// 辺 (par[c], c) を取り除くと sz[c] 頂点と n - sz[c] 頂点に分かれるので、
// その辺を通る頂点の組は sz[c] * (n - sz[c]) 個。これで全ペアの距離の和を求める
// 入力：N、続く N - 1 行に辺 u v w（1-indexed、重み w）。頂点 1 を根にする
// 出力：全ペア（順序なし）の距離の和
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < n - 1; i++) {  // 辺は N - 1 本（M を読まない）
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    // --8<-- [start:core]
    vector<int> par(n, -1), order = {0};
    vector<long long> val(n, 0);  // val[c] = 辺 (par[c], c) の重み。根は 0
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (auto [c, w] : g[v]) {
            if (c == par[v]) continue;  // 親へ戻らない
            par[c] = v;
            val[c] = w;  // 親への辺の値を子に寄せる
            order.push_back(c);
        }
    }
    vector<long long> sz(n, 1);
    long long total = 0;
    for (int i = n - 1; i >= 1; i--) {  // 子から親へ
        int c = order[i];
        total += val[c] * sz[c] * (n - sz[c]);  // 辺 (par[c], c) を通る組の数 × 重み
        sz[par[c]] += sz[c];
    }
    // --8<-- [end:core]
    assert((int)order.size() == n && sz[0] == n);
    cout << total << '\n';
}
