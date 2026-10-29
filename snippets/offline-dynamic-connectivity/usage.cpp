#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:uf]
// 経路圧縮をしない Union-Find。併合を新しいものから順に取り消せる
struct RollbackUnionFind {
    vector<int> par, sz;
    vector<pair<int, int>> hist;  // (子にした根, 親にした根)。併合しなかったら (-1, -1)
    int components;
    RollbackUnionFind(int n) : par(n, -1), sz(n, 1), components(n) {}
    int find(int v) const {
        while (par[v] >= 0) v = par[v];
        return v;
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            hist.push_back({-1, -1});  // 何もしなくても 1 つ積み、undo の回数をそろえる
            return;
        }
        if (sz[a] < sz[b]) swap(a, b);  // union by size で木の高さを O(log N) に保つ
        par[b] = a;
        sz[a] += sz[b];
        components--;
        hist.push_back({b, a});
    }
    void undo() {
        auto [b, a] = hist.back();
        hist.pop_back();
        if (b < 0) return;
        par[b] = -1;
        sz[a] -= sz[b];
        components++;
    }
};
// --8<-- [end:uf]

// --8<-- [start:core]
// 時刻 0, 1, ..., T-1 を葉とするセグメント木。ノード k は時刻の区間 [l, r) を受け持つ
struct OfflineDynamicConnectivity {
    int T;
    vector<vector<pair<int, int>>> node_edges;
    OfflineDynamicConnectivity(int t) : T(t), node_edges(4 * max(t, 1)) {}

    // 辺 (u, v) が時刻 [a, b) に存在する。区間をちょうど覆う O(log T) 個のノードに載せる
    void add_edge(int a, int b, int u, int v) { add(1, 0, T, a, b, u, v); }
    void add(int k, int l, int r, int a, int b, int u, int v) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            node_edges[k].push_back({u, v});
            return;
        }
        int m = (l + r) / 2;
        add(2 * k, l, m, a, b, u, v);
        add(2 * k + 1, m, r, a, b, u, v);
    }

    // 葉 t に着いた時点の Union-Find は、時刻 t に存在する辺をすべて併合した状態
    template <class F>
    void run(RollbackUnionFind& uf, F on_leaf) {
        if (T > 0) dfs(1, 0, T, uf, on_leaf);
    }
    template <class F>
    void dfs(int k, int l, int r, RollbackUnionFind& uf, F& on_leaf) {
        for (auto [u, v] : node_edges[k]) uf.merge(u, v);  // 入るときに併合
        if (r - l == 1) {
            on_leaf(l);
        } else {
            int m = (l + r) / 2;
            dfs(2 * k, l, m, uf, on_leaf);
            dfs(2 * k + 1, m, r, uf, on_leaf);
        }
        for (size_t i = 0; i < node_edges[k].size(); i++) uf.undo();  // 出るときに取り消す
    }
};
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // クエリ：0 u v で辺を追加、1 u v で辺を削除、2 u v で連結か（1 か 0）、3 で連結成分の数（頂点は 1-indexed）
    // 追加の直前にその辺はなく、削除の直前にその辺はあるとする
    int n, q;
    cin >> n >> q;
    vector<array<int, 3>> qs(q);
    // --8<-- [start:usage]
    OfflineDynamicConnectivity odc(q);
    map<pair<int, int>, int> added_at;  // 今ある辺と、追加された時刻
    for (int t = 0; t < q; t++) {
        int type, u = 0, v = 0;
        cin >> type;
        if (type != 3) {
            cin >> u >> v;
            u--, v--;  // 1-indexed → 0-indexed
        }
        qs[t] = {type, u, v};
        pair<int, int> e = {min(u, v), max(u, v)};
        if (type == 0) added_at[e] = t;
        if (type == 1) {
            odc.add_edge(added_at[e], t, u, v);  // 時刻 t（削除の直後）にはもうない
            added_at.erase(e);
        }
    }
    for (auto [e, a] : added_at) odc.add_edge(a, q, e.first, e.second);  // 最後まで残る辺

    RollbackUnionFind uf(n);
    vector<long long> ans(q, -1);
    odc.run(uf, [&](int t) {
        auto [type, u, v] = qs[t];
        if (type == 2) ans[t] = (uf.find(u) == uf.find(v));
        if (type == 3) ans[t] = uf.components;
    });
    // --8<-- [end:usage]
    for (int t = 0; t < q; t++) {
        if (qs[t][0] >= 2) cout << ans[t] << '\n';
    }
    assert(uf.hist.empty() && uf.components == n);  // すべて取り消されて初めの状態に戻る
}
