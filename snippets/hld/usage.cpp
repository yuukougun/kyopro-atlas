// HL 分解：頂点の値の 1 点変更と、パス u–v 上の最大値の取得（ACL の segtree を番号の列に載せる）
// 入力：N Q、A_1 … A_N、木の辺 N - 1 本、クエリ Q 行（0 v x：頂点 v の値を x にする、1 u v：パス u–v 上の最大値）。
// 頂点は 1-indexed。
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:build]
struct HLD {
    int n;
    vector<int> par, dep, sz, heavy, head, in;  // in[v]：番号（重い子を先に振る）
    HLD(const vector<vector<int>>& g, int root = 0)
        : n(g.size()), par(n, -1), dep(n, 0), sz(n, 1), heavy(n, -1), head(n), in(n) {
        // 1 回目：部分木サイズと重い子（部分木が最大の子）を求める
        auto dfs1 = [&](auto&& self, int v, int p) -> void {
            for (int c : g[v]) {
                if (c == p) continue;
                par[c] = v;
                dep[c] = dep[v] + 1;
                self(self, c, v);
                sz[v] += sz[c];
                if (heavy[v] == -1 || sz[c] > sz[heavy[v]]) heavy[v] = c;
            }
        };
        // 2 回目：重い子を先に訪れて番号を振る。重いパスの番号が連続する
        int t = 0;
        auto dfs2 = [&](auto&& self, int v, int h) -> void {
            head[v] = h;
            in[v] = t++;
            if (heavy[v] != -1) self(self, heavy[v], h);   // 重い子は同じパスを続ける
            for (int c : g[v]) {
                if (c == par[v] || c == heavy[v]) continue;
                self(self, c, c);                          // 軽い子は新しいパスの先頭
            }
        };
        dfs1(dfs1, root, -1);
        dfs2(dfs2, root, root);
    }
    // --8<-- [end:build]
    // --8<-- [start:path]
    // パス u–v を、番号の半開区間 [l, r) の列に分ける（O(log N) 個）
    vector<pair<int, int>> path(int u, int v) const {
        vector<pair<int, int>> res;
        while (head[u] != head[v]) {
            // 先頭が深い方のパスを丸ごと取り、先頭の親へ上がる
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            res.push_back({in[head[u]], in[u] + 1});
            u = par[head[u]];
        }
        if (in[u] > in[v]) swap(u, v);
        res.push_back({in[u], in[v] + 1});  // 同じパスに来たら、浅い方（LCA）から深い方まで
        return res;
    }
    // --8<-- [end:path]
    // --8<-- [start:ordered]
    // 非可換な演算用：u から v への順に並べた区間。rev が true の区間は番号の逆順にたどる
    vector<tuple<int, int, bool>> path_ordered(int u, int v) const {
        vector<tuple<int, int, bool>> up, down;  // u 側（上る）と v 側（下る）を分けて積む
        while (head[u] != head[v]) {
            if (dep[head[u]] >= dep[head[v]]) {
                up.push_back({in[head[u]], in[u] + 1, true});    // 深い方から浅い方へ：逆順
                u = par[head[u]];
            } else {
                down.push_back({in[head[v]], in[v] + 1, false}); // 浅い方から深い方へ：番号の順
                v = par[head[v]];
            }
        }
        if (dep[u] >= dep[v]) up.push_back({in[v], in[u] + 1, true});
        else up.push_back({in[u], in[v] + 1, false});
        up.insert(up.end(), down.rbegin(), down.rend());     // v 側は見つけた順と逆につなぐ
        return up;
    }
    // --8<-- [end:ordered]
    // --8<-- [start:lca]
    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    // 部分木 v は [in[v], in[v] + sz[v])
    // --8<-- [end:lca]
};

long long op(long long a, long long b) { return max(a, b); }
long long e() { return LLONG_MIN; }

// 愚直な解と比べる：親をたどってパスの最大値を求める
long long brute(const HLD& h, const vector<long long>& a, int u, int v) {
    long long res = LLONG_MIN;
    while (u != v) {
        if (h.dep[u] < h.dep[v]) swap(u, v);
        res = max(res, a[u]);
        u = h.par[u];
    }
    return max(res, a[u]);
}

void self_test() {
    mt19937 rng(1);
    for (int iter = 0; iter < 200; iter++) {
        int n = rng() % 30 + 1;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; v++) {
            int p = rng() % v;
            g[p].push_back(v);
            g[v].push_back(p);
        }
        HLD h(g);
        // 根からの軽い辺の本数は log2 N 以下
        for (int v = 0; v < n; v++) {
            int light = 0;
            for (int x = v; h.par[x] != -1; x = h.par[x])
                if (h.heavy[h.par[x]] != x) light++;
            assert((1 << light) <= n);
        }
        vector<long long> a(n);
        atcoder::segtree<long long, op, e> seg(n);
        for (int v = 0; v < n; v++) {
            a[v] = rng() % 100;
            seg.set(h.in[v], a[v]);
        }
        for (int q = 0; q < 50; q++) {
            int u = rng() % n, v = rng() % n;
            long long res = LLONG_MIN;
            for (auto [l, r] : h.path(u, v)) res = max(res, seg.prod(l, r));
            assert(res == brute(h, a, u, v));
            int w = rng() % n;
            a[w] = rng() % 100;
            seg.set(h.in[w], a[w]);
        }
    }
}

// 非可換な演算の試験（Vertex Set Path Composite 相当）：頂点の 1 次関数を u から v の順に合成する
const long long MOD = 998244353;
struct F { long long a, b; };  // x -> a x + b
F then_(F f, F g) { return {f.a * g.a % MOD, (f.b * g.a + g.b) % MOD}; }  // f の後に g
F id_() { return {1, 0}; }
F op_fwd(F l, F r) { return then_(l, r); }   // 番号の小さい方から合成
F op_rev(F l, F r) { return then_(r, l); }   // 番号の大きい方から合成

void self_test_composite() {
    mt19937 rng(2);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 30 + 1;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; v++) {
            int p = rng() % v;
            g[p].push_back(v);
            g[v].push_back(p);
        }
        HLD h(g, rng() % n);
        vector<F> f(n);
        atcoder::segtree<F, op_fwd, id_> fwd(n);
        atcoder::segtree<F, op_rev, id_> rev(n);
        auto put = [&](int v, F x) {
            f[v] = x;
            fwd.set(h.in[v], x);
            rev.set(h.in[v], x);
        };
        for (int v = 0; v < n; v++) put(v, {(long long)(rng() % 100 + 1), (long long)(rng() % 100)});
        for (int q = 0; q < 50; q++) {
            int u = rng() % n, v = rng() % n;
            F res = id_();
            for (auto [l, r, rv] : h.path_ordered(u, v)) res = then_(res, rv ? rev.prod(l, r) : fwd.prod(l, r));
            // 愚直：u から lca へ上り、lca から v へ下る順に頂点を並べて合成する
            int w = h.lca(u, v);
            vector<int> left, right;
            for (int x = u; x != w; x = h.par[x]) left.push_back(x);
            left.push_back(w);
            for (int x = v; x != w; x = h.par[x]) right.push_back(x);
            left.insert(left.end(), right.rbegin(), right.rend());
            F naive = id_();
            for (int x : left) naive = then_(naive, f[x]);
            assert(res.a == naive.a && res.b == naive.b);
            put(rng() % n, {(long long)(rng() % 100 + 1), (long long)(rng() % 100)});
        }
    }
}

int main() {
    self_test();
    self_test_composite();
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HLD h(g);
    // --8<-- [start:query]
    atcoder::segtree<long long, op, e> seg(n);       // 番号 in[v] の位置に頂点 v の値を置く
    for (int v = 0; v < n; v++) seg.set(h.in[v], a[v]);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int v;
            long long x;
            cin >> v >> x;
            v--;                                      // 1-indexed → 0-indexed
            seg.set(h.in[v], x);                      // 頂点 v の値を x にする
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;                                 // 1-indexed → 0-indexed
            long long res = e();
            for (auto [l, r] : h.path(u, v)) res = op(res, seg.prod(l, r));  // 区間ごとに集約
            cout << res << '\n';
        }
    }
    // --8<-- [end:query]
}
