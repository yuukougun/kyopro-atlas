// 根付き木の DFS：親・深さ・部分木サイズ・行きがけ番号・行きがけ順・帰りがけ順を 1 回の DFS で求める
// 入力：N、続く N - 1 行に辺 u v（1-indexed）。頂点 1 を根にする。隣は入力の順に調べる
// 出力：行きがけ順、帰りがけ順（1-indexed）、続いて各頂点の「親（根は 0） 深さ 部分木サイズ 行きがけ番号（0 始まり）」
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
    vector<int> par(n, -1), dep(n, 0), sz(n, 1), in(n);
    vector<int> pre, post;  // 行きがけ順・帰りがけ順
    auto dfs = [&](auto&& self, int v, int p) -> void {
        par[v] = p;
        in[v] = (int)pre.size();  // 行きがけ：入った順の番号
        pre.push_back(v);
        for (int c : g[v]) {
            if (c == p) continue;  // 親へ戻らない（木なので訪問済みの印は要らない）
            dep[c] = dep[v] + 1;   // 親の値から子の値を決める（上から下へ）
            self(self, c, v);
            sz[v] += sz[c];        // 子の結果を親へ集める（下から上へ）
        }
        post.push_back(v);  // 帰りがけ：子をすべて終えた
    };
    dfs(dfs, 0, -1);
    // --8<-- [end:core]
    assert((int)pre.size() == n && (int)post.size() == n && sz[0] == n);
    for (int v = 0; v < n; v++) {
        assert(pre[in[v]] == v);
        // 部分木は行きがけ順の区間 [in[v], in[v] + sz[v]) に並ぶ（親の区間の内側にあることを 1 段ずつ確かめる）
        if (v != 0) {
            int p = par[v];
            assert(in[p] < in[v] && in[v] + sz[v] <= in[p] + sz[p]);
        }
    }
    for (int i = 0; i < n; i++) cout << pre[i] + 1 << (i + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) cout << post[i] + 1 << (i + 1 < n ? ' ' : '\n');
    for (int v = 0; v < n; v++) cout << par[v] + 1 << ' ' << dep[v] << ' ' << sz[v] << ' ' << in[v] << '\n';
}
