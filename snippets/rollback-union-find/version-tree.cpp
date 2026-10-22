// ロールバックできる Union-Find（経路圧縮なし・union by size・書き換えの記録をスタックに積む）と、
// それを版の木の DFS に使って Library Checker「Persistent Unionfind」の形の問題をオフラインで解く例。
// 入力は N Q と、Q 行の「t k u v」（0-indexed）。G_{-1} は辺のない N 頂点のグラフ。
//   t = 0：G_k に辺 (u, v) を足したグラフを G_i とする
//   t = 1：G_k で u と v が連結なら 1、そうでなければ 0 を出力する
// 版 G_k を頂点 k + 1 とする木を作り、入るとき併合・出るとき取り消す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct RollbackUnionFind {
    vector<int> par;                  // 根なら −(大きさ)、根でなければ親
    vector<pair<int, int>> history;   // (書き換えた位置, 元の値)。併合 1 回につき 2 件

    explicit RollbackUnionFind(int n) : par(n, -1) {}

    int leader(int v) const {         // 経路圧縮をしない。深さは log2(N) 以下
        while (par[v] >= 0) v = par[v];
        return v;
    }
    bool same(int a, int b) const { return leader(a) == leader(b); }
    int size(int v) const { return -par[leader(v)]; }

    bool merge(int a, int b) {
        a = leader(a), b = leader(b);
        history.push_back({a, par[a]});  // 同じ成分でも 2 件積み、undo と 1 対 1 にする
        history.push_back({b, par[b]});
        if (a == b) return false;
        if (-par[a] < -par[b]) swap(a, b);  // 小さい方 b を大きい方 a の下へ
        par[a] += par[b];
        par[b] = a;
        return true;
    }
    void undo() {                     // 最後の merge を取り消す。O(1)
        for (int k = 0; k < 2; k++) {
            auto [i, old] = history.back();
            history.pop_back();
            par[i] = old;
        }
    }
    int snapshot() const { return (int)history.size() / 2; }  // ここまでの merge の回数
    void rollback(int s) {            // merge の回数が s の時点まで戻す
        while ((int)history.size() > 2 * s) undo();
    }
};
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> t(q), u(q), v(q);
    // --8<-- [start:dfs]
    vector<vector<int>> child(q + 1);              // 頂点 k + 1 が版 G_k（頂点 0 が G_{-1}）
    vector<vector<int>> ask(q + 1);                // 頂点ごとの質問（クエリの番号）
    for (int i = 0; i < q; i++) {
        int k;
        cin >> t[i] >> k >> u[i] >> v[i];
        if (t[i] == 0) child[k + 1].push_back(i + 1);  // G_i は G_k に辺を足したもの
        else ask[k + 1].push_back(i);
    }
    RollbackUnionFind uf(n);
    vector<int> ans(q, -1);
    vector<int> st = {0};                          // x ≥ 0 は「x に入る」、~x は「x から出る」
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        if (x < 0) {                               // 出る：入るときの併合を取り消す
            if (~x > 0) uf.undo();
            continue;
        }
        if (x > 0) uf.merge(u[x - 1], v[x - 1]);   // 入る：この版を作った辺を足す
        for (int i : ask[x]) ans[i] = uf.same(u[i], v[i]) ? 1 : 0;
        st.push_back(~x);                          // 子より先に積み、子孫の後に取り出す
        for (int c : child[x]) st.push_back(c);
    }
    // --8<-- [end:dfs]
    assert(uf.history.empty());                    // DFS の後はすべて取り消されている
    for (int i = 0; i < q; i++) {
        if (t[i] == 1) cout << ans[i] << '\n';
    }

    // snapshot と rollback の確かめ
    RollbackUnionFind w(4);
    w.merge(0, 1);
    int s = w.snapshot();
    w.merge(2, 3);
    w.merge(1, 2);
    assert(w.size(0) == 4);
    w.merge(0, 3);                                 // 同じ成分どうし（記録は積まれる）
    w.rollback(s);
    assert(w.same(0, 1) && !w.same(1, 2) && w.size(2) == 1);
}
