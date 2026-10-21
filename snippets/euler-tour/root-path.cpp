// オイラーツアー：辺の重みの変更を子の部分木への区間加算にし、根からの距離 S[v] を一点の取得にする
// 入力：N Q、続く N-1 行は「p_i w_i」（頂点 i の親と、辺 (p_i, i) の重み。根は頂点 0）
//       続く Q 行は「0 c w」（辺 (par[c], c) の重みを w にする）か「1 u v」（u と v の距離を出力）
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    vector<int> par(n, -1);
    vector<long long> w(n, 0);  // w[c]：辺 (par[c], c) の重みを子 c に置く
    for (int i = 1; i < n; i++) {
        cin >> par[i] >> w[i];
        g[par[i]].push_back(i);
    }
    vector<int> in(n), out(n), dep(n, 0);
    int timer = 0;
    auto dfs = [&](auto&& self, int v) -> void {
        in[v] = timer++;
        for (int c : g[v]) {
            dep[c] = dep[v] + 1;
            self(self, c);
        }
        out[v] = timer;
    };
    dfs(dfs, 0);
    // 確かめ用の素朴な LCA（1 回 O(N)）。本番は LCA のページの方法で O(log N) にする
    auto lca = [&](int u, int v) {
        while (dep[u] > dep[v]) u = par[u];
        while (dep[v] > dep[u]) v = par[v];
        while (u != v) u = par[u], v = par[v];
        return u;
    };

    // --8<-- [start:core]
    // 差分の BIT：区間 [l, r) に x を加える = 位置 l に +x、位置 r に -x
    atcoder::fenwick_tree<long long> fw(n + 1);
    auto range_add = [&](int l, int r, long long x) { fw.add(l, x); fw.add(r, -x); };
    auto S = [&](int v) { return fw.sum(0, in[v] + 1); };  // 根から v までの重みの和

    for (int c = 1; c < n; c++) range_add(in[c], out[c], w[c]);  // 辺の重みは子の部分木の全員に効く

    auto set_weight = [&](int c, long long nw) {
        range_add(in[c], out[c], nw - w[c]);  // 差分だけ足す
        w[c] = nw;
    };
    // lca は LCA のページの方法（ダブリングなら 1 回 O(log N)）。ここでは確かめ用の素朴な版
    auto dist = [&](int u, int v) { return S(u) + S(v) - 2 * S(lca(u, v)); };
    // --8<-- [end:core]

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int c;
            long long nw;
            cin >> c >> nw;
            set_weight(c, nw);
        } else {
            int u, v;
            cin >> u >> v;
            long long res = dist(u, v);
            long long check = 0;  // 確かめ：親をたどって辺の重みを足す
            int a = u, b = v;
            while (dep[a] > dep[b]) check += w[a], a = par[a];
            while (dep[b] > dep[a]) check += w[b], b = par[b];
            while (a != b) check += w[a] + w[b], a = par[a], b = par[b];
            assert(res == check);
            cout << res << '\n';
        }
    }
}
