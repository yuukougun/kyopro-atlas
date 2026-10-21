// 再帰を使わない走査：根から BFS した順 order を作り、前から読んで深さを、逆から読んで部分木サイズを求める
// 入力：N、続く N - 1 行に辺 u v（1-indexed）。頂点 1 を根にする
// 出力：BFS 順（1-indexed）、続いて各頂点の「深さ 部分木サイズ」
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // --8<-- [start:core]
    vector<int> par(n, -1), dep(n, 0), order = {0};  // order は配列をキューとして使う
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;  // 親へ戻らない
            par[c] = v;
            dep[c] = dep[v] + 1;  // 前から読む：親は子より前にあるので確定済み
            order.push_back(c);
        }
    }
    vector<int> sz(n, 1);
    for (int i = n - 1; i >= 1; i--) {  // 逆から読む：子は親より先に確定する
        int v = order[i];
        sz[par[v]] += sz[v];
    }
    // --8<-- [end:core]
    assert((int)order.size() == n && sz[0] == n);
    for (int i = 1; i < n; i++) assert(dep[order[i - 1]] <= dep[order[i]]);  // 深さの順に並ぶ
    for (int i = 0; i < n; i++) cout << order[i] + 1 << (i + 1 < n ? ' ' : '\n');
    for (int v = 0; v < n; v++) cout << dep[v] << ' ' << sz[v] << '\n';
}
