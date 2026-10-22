#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// 併合過程の木。葉 0..n-1 が元の頂点、n 以降が併合のたびに作る頂点。
// 辺は (重み, u, v) を重みの昇順（または時刻の順）に渡す。
struct MergeTree {
    int n, LOG = 1;
    vector<int> par;              // 親（根は自分自身）
    vector<long long> wt;         // 頂点の重み（葉は LLONG_MIN）
    vector<array<int, 2>> ch;     // 子（葉は -1）
    vector<int> lo, hi;           // 部分木の葉は、葉の DFS 順で [lo, hi)
    vector<vector<int>> up;       // up[k][v]：2^k 個上の祖先

    // --8<-- [start:build]
    MergeTree(int n_, const vector<tuple<long long, int, int>>& edges) : n(n_) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        wt.assign(n, LLONG_MIN);
        ch.assign(n, {-1, -1});
        atcoder::dsu d(n);
        vector<int> top(n);       // 代表元 r の成分を表す木の頂点が top[r]
        iota(top.begin(), top.end(), 0);
        for (auto [w, u, v] : edges) {
            int a = d.leader(u), b = d.leader(v);
            if (a == b) continue;  // 成分が変わらない辺は頂点を作らない
            int x = par.size();    // 新しい頂点
            par.push_back(x);
            wt.push_back(w);
            ch.push_back({top[a], top[b]});
            par[top[a]] = x;
            par[top[b]] = x;
            top[d.merge(a, b)] = x;  // merge の返す新しい代表元に付け替える
        }
        // --8<-- [end:build]
        int sz = par.size();
        // 葉に DFS 順の番号を振り、各頂点の葉の区間を求める（非再帰）
        lo.assign(sz, 0);
        hi.assign(sz, 0);
        int cnt = 0;
        for (int r = 0; r < sz; r++) {
            if (par[r] != r) continue;
            vector<int> st = {r};
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                if (v >= 0) {
                    lo[v] = cnt;
                    if (v < n) {
                        cnt++;
                        hi[v] = cnt;
                        continue;
                    }
                    st.push_back(~v);
                    st.push_back(ch[v][1]);
                    st.push_back(ch[v][0]);
                } else {
                    hi[~v] = cnt;
                }
            }
        }
        while ((1 << LOG) < sz) LOG++;
        up.assign(LOG, par);
        for (int k = 1; k < LOG; k++)
            for (int v = 0; v < sz; v++) up[k][v] = up[k - 1][up[k - 1][v]];
    }

    // --8<-- [start:query]
    // 重み t 以下の辺だけを使ったときの x の成分を表す頂点（その葉が成分）
    int group(int x, long long t) const {
        int v = x;
        for (int k = LOG - 1; k >= 0; k--)
            if (wt[up[k][v]] <= t) v = up[k][v];  // 重みは根に近いほど大きい
        return v;
    }
    bool contains(int a, int leaf) const { return lo[a] <= lo[leaf] && lo[leaf] < hi[a]; }
    // u と v を結ぶパスの最大の辺の最小値。つながらないなら nullopt
    optional<long long> bottleneck(int u, int v) const {
        if (u == v) return 0;  // 辺を使わないので 0 を返す約束。重みが負なら問題に合わせて決める
        if (contains(u, v)) return wt[u];
        for (int k = LOG - 1; k >= 0; k--)
            if (!contains(up[k][u], v)) u = up[k][u];
        int p = par[u];             // u の親が LCA（v を含む最も深い祖先）
        if (!contains(p, v)) return nullopt;  // 別の木（非連結）
        return wt[p];
    }
    // --8<-- [end:query]
};

// 重み t 以下の辺だけの Union-Find で確かめる
void self_test() {
    mt19937 rng(1);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 7 + 1, m = rng() % 10;
        vector<tuple<long long, int, int>> e;
        for (int i = 0; i < m; i++) e.push_back({(long long)(rng() % 5), (int)(rng() % n), (int)(rng() % n)});
        sort(e.begin(), e.end());
        MergeTree mt(n, e);
        for (long long t = -1; t <= 5; t++) {
            atcoder::dsu d(n);
            for (auto [w, u, v] : e)
                if (w <= t) d.merge(u, v);
            for (int x = 0; x < n; x++) {
                int g = mt.group(x, t);
                assert(mt.hi[g] - mt.lo[g] == d.size(x));
                for (int y = 0; y < n; y++) assert(mt.contains(g, y) == d.same(x, y));
            }
        }
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) {
                optional<long long> want;
                if (u == v) want = 0;
                for (long long t = 0; t <= 5 && !want; t++) {
                    atcoder::dsu d(n);
                    for (auto [w, a, b] : e)
                        if (w <= t) d.merge(a, b);
                    if (d.same(u, v)) want = t;
                }
                assert(mt.bottleneck(u, v) == want);
            }
    }
}

int main() {
    self_test();
    int n, m;
    cin >> n >> m;
    vector<tuple<long long, int, int>> e(m);
    for (auto& [w, u, v] : e) cin >> u >> v >> w;
    sort(e.begin(), e.end());
    MergeTree mt(n, e);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        auto b = mt.bottleneck(u, v);
        cout << (b ? *b : -1) << '\n';
    }
}
