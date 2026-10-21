// DSU on Tree：すべての部分木について、色の種類数を配列 1 本で求める
// 入力：N、P_1 … P_{N-1}（頂点 i の親。0-indexed で P_i < i、根は 0）、C_0 … C_{N-1}（色。0 以上 N 未満）
// 出力：各頂点の部分木にある色の種類数を空白区切りで
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ch(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        ch[p].push_back(i);
    }
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    // --8<-- [start:core]
    // 前処理：部分木サイズ sz と重い子 heavy、行きがけ順 ord と in・out（部分木 v は ord[in[v], out[v])）
    vector<int> sz(n, 1), heavy(n, -1), in(n), out(n), ord;
    auto dfs1 = [&](auto&& self, int v) -> void {
        in[v] = ord.size();
        ord.push_back(v);
        for (int u : ch[v]) {
            self(self, u);
            sz[v] += sz[u];
            if (heavy[v] == -1 || sz[u] > sz[heavy[v]]) heavy[v] = u;
        }
        out[v] = ord.size();
    };
    dfs1(dfs1, 0);

    vector<int> cnt(n, 0), ans(n);  // cnt[x]：今数えている頂点のうち色 x の個数
    int kinds = 0;                  // cnt[x] > 0 の色の数
    auto add = [&](int v) { if (cnt[c[v]]++ == 0) kinds++; };
    auto remove = [&](int v) { if (--cnt[c[v]] == 0) kinds--; };

    // keep が true なら、v の部分木を数えた状態のまま返る。false なら空に戻して返る
    auto dfs2 = [&](auto&& self, int v, bool keep) -> void {
        for (int u : ch[v]) if (u != heavy[v]) self(self, u, false);  // 軽い子を先に（使ったら消す）
        if (heavy[v] != -1) self(self, heavy[v], true);                // 重い子の分は残す
        for (int u : ch[v]) {
            if (u == heavy[v]) continue;
            for (int i = in[u]; i < out[u]; i++) add(ord[i]);          // 軽い子の部分木を数え直す
        }
        add(v);
        ans[v] = kinds;
        if (!keep) {
            for (int i = in[v]; i < out[v]; i++) remove(ord[i]);
        }
    };
    dfs2(dfs2, 0, true);
    // --8<-- [end:core]

    // 素朴な方法：子の集合を親へ足す（P_i < i なので番号の大きい順に処理できる）
    vector<set<int>> s(n);
    for (int i = 0; i < n; i++) s[i].insert(c[i]);
    vector<int> par(n, -1);
    for (int v = 0; v < n; v++) for (int u : ch[v]) par[u] = v;
    for (int i = n - 1; i >= 1; i--) for (int x : s[i]) s[par[i]].insert(x);
    for (int i = 0; i < n; i++) assert(ans[i] == (int)s[i].size());

    for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 < n ? ' ' : '\n');
}
