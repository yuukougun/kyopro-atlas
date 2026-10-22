#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 時刻 1, 2, ... に 1 回ずつ併合し、過去の時刻 t での根・大きさを答える
struct PartiallyPersistentUnionFind {
    static constexpr int INF = INT_MAX;
    int now = 0;                            // 最後に行った操作の時刻
    vector<int> par, sz, tm;                // tm[v]：v が根でなくなった時刻（根なら INF）
    vector<vector<pair<int, int>>> hist;    // hist[r]：根 r の（時刻, 大きさ）の履歴

    PartiallyPersistentUnionFind(int n)
        : par(n), sz(n, 1), tm(n, INF), hist(n, {{0, 1}}) {
        iota(par.begin(), par.end(), 0);
    }
    // 時刻 t の時点の根。経路圧縮はしない（過去の形を壊すため）
    int find(int x, int t) const {
        while (tm[x] <= t) x = par[x];
        return x;
    }
    bool same(int x, int y, int t) const { return find(x, t) == find(y, t); }
    // 時刻 t の時点で x を含む集合の大きさ
    int size(int x, int t) const {
        const auto& h = hist[find(x, t)];
        auto it = upper_bound(h.begin(), h.end(), make_pair(t, INF));
        return prev(it)->second;
    }
    // 最新の状態で併合する。同じ集合でも時刻は 1 進める
    bool merge(int x, int y) {
        ++now;
        x = find(x, now);
        y = find(y, now);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);      // union by size（小さい y を x の下へ）
        par[y] = x;
        tm[y] = now;
        sz[x] += sz[y];
        hist[x].push_back({now, sz[x]});
        return true;
    }
};
// --8<-- [end:core]

// --8<-- [start:first-same]
// x と y が初めて同じ集合になった時刻（ならなければ -1）を時刻の二分探索で求める
int first_same(const PartiallyPersistentUnionFind& uf, int x, int y) {
    if (!uf.same(x, y, uf.now)) return -1;
    int ng = -1, ok = uf.now;               // same(ok) は真、same(ng) は偽
    while (ok - ng > 1) {
        int mid = (ok + ng) / 2;
        (uf.same(x, y, mid) ? ok : ng) = mid;
    }
    return ok;
}
// --8<-- [end:first-same]

// --8<-- [start:climb]
// 二分探索なし：時刻の小さい側から登る。登った辺の時刻の最大が答え
int first_same_climb(const PartiallyPersistentUnionFind& uf, int x, int y) {
    int ans = 0;
    while (x != y) {
        if (uf.tm[x] > uf.tm[y]) swap(x, y);   // 時刻の小さい側を登る
        if (uf.tm[x] == uf.INF) return -1;     // 両方とも根で別の木
        ans = uf.tm[x];
        x = uf.par[x];
    }
    return ans;
}
// --8<-- [end:climb]

// 素朴な方法（各時刻の状態を作り直す）と突き合わせる
void self_check() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 7 + 1, m = rng() % 10;
        PartiallyPersistentUnionFind uf(n);
        vector<pair<int, int>> ops(m);
        for (auto& [a, b] : ops) {
            a = rng() % n;
            b = rng() % n;
            uf.merge(a, b);
        }
        for (int t = 0; t <= m; t++) {
            vector<int> g(n);
            iota(g.begin(), g.end(), 0);
            for (int i = 0; i < t; i++) {
                int ga = g[ops[i].first], gb = g[ops[i].second];
                for (int& v : g) if (v == gb) v = ga;
            }
            for (int x = 0; x < n; x++) {
                assert(uf.size(x, t) == (int)count(g.begin(), g.end(), g[x]));
                for (int y = 0; y < n; y++) assert(uf.same(x, y, t) == (g[x] == g[y]));
            }
        }
        for (int x = 0; x < n; x++)
            for (int y = 0; y < n; y++) assert(first_same(uf, x, y) == first_same_climb(uf, x, y));
    }
}

int main() {
    self_check();
    int n, m;
    cin >> n >> m;
    PartiallyPersistentUnionFind uf(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        uf.merge(a - 1, b - 1);             // i + 1 回目の操作は時刻 i + 1
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        cout << first_same(uf, x, y) << ' ' << uf.size(x, uf.now / 2) << '\n';
    }
}
