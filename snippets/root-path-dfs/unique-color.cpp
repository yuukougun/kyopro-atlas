// 根からのパス上の色の出現回数を DFS で持ち回る（入るとき +1、出るとき −1）。
// 頂点 v の色が、根から v までのパス上で v のほかに現れなければ v を「良い頂点」とし、番号の昇順に出力する。
// 再帰版と、「入る」「出る」の 2 種類をスタックに積む非再帰版が同じ答えを出すことを assert で確かめる。
// 入力は N、色 c_1 … c_N（1 以上 10^5 以下）、辺 N − 1 本（1-indexed）。根は頂点 1。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    const int C = 100001;

    // --8<-- [start:core]
    vector<int> cnt(C, 0);  // cnt[x] = 根から今の頂点までのパス上にある色 x の頂点の数
    vector<bool> good(n, false);
    auto dfs = [&](auto&& self, int v, int p) -> void {
        if (cnt[c[v]] == 0) good[v] = true;  // 祖先に同じ色がない
        cnt[c[v]]++;                          // 入る：パスに v を足す
        for (int to : g[v]) {
            if (to != p) self(self, to, v);
        }
        cnt[c[v]]--;                          // 出る：パスから v を除く（足した分だけ戻す）
    };
    dfs(dfs, 0, -1);
    // --8<-- [end:core]

    // --8<-- [start:iterative]
    vector<int> cnt2(C, 0);
    vector<bool> good2(n, false);
    vector<int> par(n, -1);
    vector<int> st = {0};  // v ≥ 0 は「v に入る」、~v（負の数）は「v から出る」
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        if (x < 0) {  // 出る：子孫はすべて出た後なので、v の変更を戻す
            cnt2[c[~x]]--;
            continue;
        }
        if (cnt2[c[x]] == 0) good2[x] = true;
        cnt2[c[x]]++;
        st.push_back(~x);  // 子より先に積むので、子孫がすべて出た後に取り出される
        for (int to : g[x]) {
            if (to == par[x]) continue;
            par[to] = x;
            st.push_back(to);
        }
    }
    // --8<-- [end:iterative]
    assert(good == good2);
    for (int x = 0; x < C; x++) assert(cnt[x] == 0 && cnt2[x] == 0);  // すべて戻っている

    for (int v = 0; v < n; v++) {
        if (good[v]) cout << v + 1 << '\n';
    }
}
