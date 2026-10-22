#include <bits/stdc++.h>
#include <atcoder/dsu>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:det]
// 行列式（mod 998244353）。掃き出しで上三角にし、対角成分の積を返す。O(n^3)
mint det(vector<vector<mint>> a) {
    int n = a.size();
    mint res = 1;
    for (int c = 0; c < n; c++) {
        int p = -1;
        for (int r = c; r < n; r++) {
            if (a[r][c] != 0) { p = r; break; }
        }
        if (p == -1) return 0;           // この列がすべて 0 なら行列式は 0
        if (p != c) { swap(a[p], a[c]); res = -res; }  // 行の交換で符号が反転する
        res *= a[c][c];
        mint inv = a[c][c].inv();
        for (int r = c + 1; r < n; r++) {
            mint f = a[r][c] * inv;
            if (f == 0) continue;
            for (int k = c; k < n; k++) a[r][k] -= f * a[c][k];
        }
    }
    return res;
}
// --8<-- [end:det]

// --8<-- [start:laplacian]
// 無向グラフの全域木の数。ラプラシアン行列から頂点 0 の行と列を除いた行列式
mint count_spanning_trees(int n, const vector<pair<int, int>>& edges) {
    vector<vector<mint>> L(n, vector<mint>(n, 0));
    for (auto [u, v] : edges) {
        if (u == v) continue;            // 自己ループは全域木に使えないので無視する
        L[u][u] += 1; L[v][v] += 1;      // 多重辺はそのまま足す
        L[u][v] -= 1; L[v][u] -= 1;
    }
    vector<vector<mint>> m(n - 1, vector<mint>(n - 1));
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++) m[i - 1][j - 1] = L[i][j];
    return det(m);                       // n = 1 なら空の行列で 1
}

// 有向グラフで、根 r からすべての頂点へ向かう全域木の数。
// 対角に入次数を置き（自己ループは対角で打ち消すので除く）、r の行と列を除く
mint count_out_arborescences(int n, const vector<pair<int, int>>& edges, int r) {
    vector<vector<mint>> L(n, vector<mint>(n, 0));
    for (auto [u, v] : edges) {
        if (u == v) continue;
        L[v][v] += 1;
        L[u][v] -= 1;
    }
    vector<int> id;
    for (int i = 0; i < n; i++) if (i != r) id.push_back(i);
    vector<vector<mint>> m(n - 1, vector<mint>(n - 1));
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++) m[i][j] = L[id[i]][id[j]];
    return det(m);
}
// --8<-- [end:laplacian]

// --8<-- [start:best]
// 有向グラフのオイラー閉路の数（辺は区別し、巡回シフトで移り合うものは同じとみなす）。
// BEST 定理：根付き全域木の数 × 各頂点の (出次数 - 1)! の積
mint count_eulerian_circuits(int n, const vector<pair<int, int>>& edges) {
    vector<int> in(n, 0), out(n, 0);
    atcoder::dsu d(n);
    for (auto [u, v] : edges) { out[u]++; in[v]++; d.merge(u, v); }
    for (int v = 0; v < n; v++) if (in[v] != out[v]) return 0;
    if (edges.empty()) return 1;         // 辺が 0 本なら空の閉路 1 つとみなす（0 とする約束なら変える）
    int root = edges[0].first;
    vector<int> idx(n, -1);              // 辺のある頂点だけを残し、番号を詰める
    int k = 0;
    for (int v = 0; v < n; v++) {
        if (out[v] == 0) continue;
        if (!d.same(v, root)) return 0;  // 辺が 2 つ以上の成分に分かれている
        idx[v] = k++;
    }
    vector<pair<int, int>> e2;
    for (auto [u, v] : edges) e2.push_back({idx[u], idx[v]});
    // 入次数＝出次数なので、根へ向かう木と根から出る木の数は等しい
    mint res = count_out_arborescences(k, e2, idx[root]);
    vector<mint> fact(edges.size() + 1, 1);
    for (int i = 1; i <= (int)edges.size(); i++) fact[i] = fact[i - 1] * i;
    for (int v = 0; v < n; v++) if (out[v] > 0) res *= fact[out[v] - 1];
    return res;
}
// --8<-- [end:best]

// ---- 小さいグラフで全列挙と比べる ----
long long brute_undirected(int n, const vector<pair<int, int>>& e) {
    int m = e.size();
    long long cnt = 0;
    for (int s = 0; s < (1 << m); s++) {
        if (__builtin_popcount(s) != n - 1) continue;
        atcoder::dsu d(n);
        bool ok = true;
        for (int i = 0; i < m; i++) if (s >> i & 1) {
            if (d.same(e[i].first, e[i].second)) { ok = false; break; }
            d.merge(e[i].first, e[i].second);
        }
        if (ok) cnt++;
    }
    return cnt;
}

long long brute_directed(int n, const vector<pair<int, int>>& e, int r) {
    int m = e.size();
    long long cnt = 0;
    for (int s = 0; s < (1 << m); s++) {
        if (__builtin_popcount(s) != n - 1) continue;
        vector<int> indeg(n, 0);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) if (s >> i & 1) {
            indeg[e[i].second]++;
            g[e[i].first].push_back(e[i].second);
        }
        if (indeg[r] != 0) continue;
        vector<bool> seen(n, false);
        vector<int> st = {r};
        seen[r] = true;
        int c = 1;
        while (!st.empty()) {
            int v = st.back(); st.pop_back();
            for (int w : g[v]) if (!seen[w]) { seen[w] = true; c++; st.push_back(w); }
        }
        if (c == n) cnt++;
    }
    return cnt;
}

long long brute_euler(const vector<pair<int, int>>& e) {
    int m = e.size();
    vector<int> p(m - 1);
    iota(p.begin(), p.end(), 1);
    long long cnt = 0;
    do {
        vector<int> seq = {0};
        for (int x : p) seq.push_back(x);
        bool ok = true;
        for (int i = 0; i < m; i++) {
            if (e[seq[i]].second != e[seq[(i + 1) % m]].first) { ok = false; break; }
        }
        if (ok) cnt++;
    } while (next_permutation(p.begin(), p.end()));
    return cnt;
}

void selftest() {
    mt19937 rng(12345);
    for (int t = 0; t < 300; t++) {
        int n = rng() % 5 + 1, m = rng() % 8;
        vector<pair<int, int>> e(m);
        for (auto& [u, v] : e) { u = rng() % n; v = rng() % n; }
        assert(count_spanning_trees(n, e).val() == brute_undirected(n, e));
        int r = rng() % n;
        assert(count_out_arborescences(n, e, r).val() == brute_directed(n, e, r));
    }
    for (int t = 0; t < 300; t++) {
        int n = rng() % 4 + 1, m = rng() % 7 + 1;
        vector<pair<int, int>> e(m);
        for (auto& [u, v] : e) { u = rng() % n; v = rng() % n; }
        assert((long long)count_eulerian_circuits(n, e).val() == brute_euler(e));
    }
}

int main() {
    string mode;
    cin >> mode;
    if (mode == "T") { selftest(); cout << "ok\n"; return 0; }
    int n, m, r = 0;
    cin >> n >> m;
    if (mode == "D") cin >> r;
    vector<pair<int, int>> e(m);
    for (auto& [u, v] : e) cin >> u >> v;
    mint ans;
    if (mode == "U") ans = count_spanning_trees(n, e);
    else if (mode == "D") ans = count_out_arborescences(n, e, r);
    else ans = count_eulerian_circuits(n, e);
    cout << ans.val() << '\n';
}
