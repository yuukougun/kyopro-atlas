// 行きがけ順と帰りがけ順：頂点 0 から DFS し、入った順（行きがけ順）と出た順（帰りがけ順）を出力する。
// 再帰版と、「入る」「出る」の 2 種類をスタックに積む非再帰版が同じ順を作ることを assert で確かめる。
// 入力は N M と辺 (u, v)（1-indexed、無向）。隣接リストは入力の順に並ぶ。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    vector<bool> seen(n, false);
    vector<int> pre, post;  // 行きがけ順・帰りがけ順
    auto dfs = [&](auto&& self, int v) -> void {
        seen[v] = true;
        pre.push_back(v);  // 行きがけ：子を調べる前の処理
        for (int to : g[v]) {
            if (!seen[to]) self(self, to);
        }
        post.push_back(v);  // 帰りがけ：子をすべて調べ終えた後の処理
    };
    dfs(dfs, 0);
    // --8<-- [end:core]

    // --8<-- [start:iterative]
    vector<bool> seen2(n, false);
    vector<int> pre2, post2;
    vector<int> st = {0};  // v ≥ 0 は「v に入る」、~v（負の数）は「v から出る」
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        if (x < 0) {  // 出る：子の処理はすべて済んでいる
            post2.push_back(~x);
            continue;
        }
        if (seen2[x]) continue;  // 積んだ後で先に訪れた頂点は飛ばす
        seen2[x] = true;
        pre2.push_back(x);
        st.push_back(~x);  // 子より先に積むので、子がすべて出た後に取り出される
        for (int i = (int)g[x].size() - 1; i >= 0; i--) {  // 逆順に積むと再帰と同じ順になる
            if (!seen2[g[x][i]]) st.push_back(g[x][i]);
        }
    }
    // --8<-- [end:iterative]
    assert(pre == pre2 && post == post2);

    for (int i = 0; i < (int)pre.size(); i++) cout << pre[i] + 1 << (i + 1 < (int)pre.size() ? ' ' : '\n');
    for (int i = 0; i < (int)post.size(); i++) cout << post[i] + 1 << (i + 1 < (int)post.size() ? ' ' : '\n');
}
