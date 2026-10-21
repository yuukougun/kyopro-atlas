// オイラーツアー：部分木を区間 [in[v], out[v]) にして、一点加算・部分木の和を BIT で答える
// 入力：N Q、a_0 … a_{N-1}、p_1 … p_{N-1}（頂点 i の親。根は頂点 0）
//       続く Q 行は「0 u x」（a_u に x を加える）か「1 u」（u の部分木の和を出力）
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> g(n);
    vector<int> par(n, -1);
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        g[par[i]].push_back(i);
    }
    // --8<-- [start:core]
    vector<int> in(n), out(n);
    int timer = 0;
    // g は子だけの隣接リストなので親を渡さない（無向の隣接リストなら int p を足して親へ戻らない）
    auto dfs = [&](auto&& self, int v) -> void {
        in[v] = timer++;               // 入ったときに次の番号を振る
        for (int c : g[v]) self(self, c);
        out[v] = timer;                // 子孫を回り終えた時点の「次の番号」
    };
    dfs(dfs, 0);                       // パス状の木では再帰が N 段になる

    atcoder::fenwick_tree<long long> fw(n);
    for (int v = 0; v < n; v++) fw.add(in[v], a[v]);  // 頂点 v の値は位置 in[v] に置く

    auto add = [&](int v, long long x) { fw.add(in[v], x); };
    auto subtree_sum = [&](int v) { return fw.sum(in[v], out[v]); };  // 半開区間
    // --8<-- [end:core]

    // 確かめ：u が v の祖先（自身を含む）なら、親をたどると u に着く
    auto is_ancestor_naive = [&](int u, int v) {
        for (int w = v; w != -1; w = par[w])
            if (w == u) return true;
        return false;
    };
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            assert(is_ancestor_naive(u, v) == (in[u] <= in[v] && in[v] < out[u]));
    assert(out[0] == n);

    for (int i = 0; i < q; i++) {
        int t, u;
        cin >> t >> u;
        if (t == 0) {
            long long x;
            cin >> x;
            add(u, x);
            a[u] += x;
        } else {
            long long res = subtree_sum(u);
            long long check = 0;
            for (int v = 0; v < n; v++)
                if (is_ancestor_naive(u, v)) check += a[v];
            assert(res == check);
            cout << res << '\n';
        }
    }
}
