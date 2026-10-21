#include <bits/stdc++.h>
using namespace std;

// 入力：n と n − 1 本の辺（頂点は 0-indexed、根は 0）、続けて q 個の質問
//   1 u v x   ：x がパス u–v 上にあれば 1、なければ 0
//   2 a b c   ：3 点の合流点
//   3 a b c d ：パス a–b と c–d の共通部分。なければ -1、あれば両端（小さい順）
//   4 u v K   ：パス u–v 上で u から K 番目の頂点（K > d(u, v) なら -1）
// 最後に、ランダムな小さい木で全探索と比べる（assert）。
struct Tree {
    int n, LOG;
    vector<int> dep;
    vector<vector<int>> up;  // up[k][v]：v の 2^k 個上の祖先（根の親は根）

    Tree(const vector<vector<int>>& g) : n(g.size()), LOG(1), dep(g.size(), -1) {
        while ((1 << LOG) < n) LOG++;
        up.assign(LOG, vector<int>(n, 0));
        queue<int> que;
        dep[0] = 0;
        que.push(0);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int c : g[v]) {
                if (dep[c] != -1) continue;
                dep[c] = dep[v] + 1;
                up[0][c] = v;
                que.push(c);
            }
        }
        for (int k = 0; k + 1 < LOG; k++) {
            for (int v = 0; v < n; v++) up[k + 1][v] = up[k][up[k][v]];
        }
    }
    int kth_ancestor(int v, int K) const {  // K ≤ dep[v] で呼ぶ
        for (int k = 0; k < LOG; k++) {
            if (K >> k & 1) v = up[k][v];
        }
        return v;
    }
    int lca(int u, int v) const {
        if (dep[u] < dep[v]) swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
        }
        return up[0][u];
    }
    int dist(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

    // --8<-- [start:on-path]
    // x がパス u–v 上にあるか。辺の重みがない（どれも 1 の）ときの距離で判定する
    bool on_path(int u, int v, int x) const {
        return dist(u, x) + dist(x, v) == dist(u, v);
    }
    // --8<-- [end:on-path]

    // --8<-- [start:meet]
    // 3 点 a, b, c を結ぶ 3 本のパスがすべて通る頂点（合流点）。
    // 3 つの LCA のうち 2 つは等しく、残りの 1 つ（最も深いもの）が答え
    int meet(int a, int b, int c) const {
        int x = lca(a, b), y = lca(b, c), z = lca(c, a);
        if (x == y) return z;
        if (y == z) return x;
        return y;  // z == x
    }
    // --8<-- [end:meet]

    // --8<-- [start:intersect]
    // パス a–b と c–d の共通部分。共通の頂点がなければ {-1, -1}、あれば共通部分のパスの両端
    pair<int, int> intersect(int a, int b, int c, int d) const {
        int l1 = lca(a, b), l2 = lca(c, d);
        int deep = dep[l1] >= dep[l2] ? l1 : l2;  // 深い方の LCA
        int other_u = deep == l1 ? c : a, other_v = deep == l1 ? d : b;
        if (!on_path(other_u, other_v, deep)) return {-1, -1};  // 深い方の LCA が他方のパス上になければ交わらない
        // 交わるとき、両端は 4 つの LCA のうち深い 2 つ
        array<int, 4> cand = {lca(a, c), lca(a, d), lca(b, c), lca(b, d)};
        sort(cand.begin(), cand.end(), [&](int x, int y) { return dep[x] > dep[y]; });
        return {cand[0], cand[1]};
    }
    // --8<-- [end:intersect]

    // --8<-- [start:kth]
    // パス u–v 上で u から K 番目の頂点（K = 0 なら u）。K > d(u, v) なら -1
    int kth_on_path(int u, int v, int K) const {
        int l = lca(u, v);
        int du = dep[u] - dep[l], dv = dep[v] - dep[l];  // u から l、v から l までの辺の数
        if (K > du + dv) return -1;
        if (K <= du) return kth_ancestor(u, K);  // u から l へ上る途中
        return kth_ancestor(v, du + dv - K);     // l から v へ下る途中は、v から上って数える
    }
    // --8<-- [end:kth]
};

// 全探索：パス u–v の頂点の列（BFS で親をたどる）
vector<int> brute_path(const vector<vector<int>>& g, int u, int v) {
    int n = g.size();
    vector<int> par(n, -2);
    queue<int> que;
    par[u] = -1;
    que.push(u);
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int y : g[x]) {
            if (par[y] != -2) continue;
            par[y] = x;
            que.push(y);
        }
    }
    vector<int> path;
    for (int x = v; x != -1; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());  // u から v の順
    return path;
}

void check(const vector<vector<int>>& g) {
    int n = g.size();
    Tree t(g);
    vector<vector<vector<int>>> path(n, vector<vector<int>>(n));
    vector<vector<vector<bool>>> in(n, vector<vector<bool>>(n, vector<bool>(n, false)));
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            path[u][v] = brute_path(g, u, v);
            for (int x : path[u][v]) in[u][v][x] = true;
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            for (int x = 0; x < n; x++) assert(t.on_path(u, v, x) == in[u][v][x]);
            for (int K = 0; K <= n; K++) {
                int want = K < (int)path[u][v].size() ? path[u][v][K] : -1;
                assert(t.kth_on_path(u, v, K) == want);
            }
            for (int c = 0; c < n; c++) {
                int m = t.meet(u, v, c);
                assert(in[u][v][m] && in[v][c][m] && in[c][u][m]);
            }
        }
    }
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int c = 0; c < n; c++) {
                for (int d = 0; d < n; d++) {
                    vector<int> common;
                    for (int x = 0; x < n; x++) {
                        if (in[a][b][x] && in[c][d][x]) common.push_back(x);
                    }
                    auto [p, q] = t.intersect(a, b, c, d);
                    if (common.empty()) {
                        assert(p == -1 && q == -1);
                        continue;
                    }
                    // 共通部分はパス p–q と一致する
                    vector<int> pq = path[p][q];
                    sort(pq.begin(), pq.end());
                    assert(pq == common);
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    Tree t(g);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            cout << (t.on_path(u, v, x) ? 1 : 0) << '\n';
        } else if (type == 2) {
            int a, b, c;
            cin >> a >> b >> c;
            cout << t.meet(a, b, c) << '\n';
        } else if (type == 3) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            auto [p, r] = t.intersect(a, b, c, d);
            if (p == -1) {
                cout << -1 << '\n';
            } else {
                cout << min(p, r) << ' ' << max(p, r) << '\n';
            }
        } else {
            int u, v, K;
            cin >> u >> v >> K;
            cout << t.kth_on_path(u, v, K) << '\n';
        }
    }

    check(g);
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int m = rng() % 9 + 1;
        vector<vector<int>> h(m);
        for (int v = 1; v < m; v++) {
            int p = rng() % v;
            h[p].push_back(v);
            h[v].push_back(p);
        }
        check(h);
    }
}
