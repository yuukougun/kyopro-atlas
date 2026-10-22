// Borůvka 法：辺が暗黙に与えられる完全グラフの最小全域木
// 頂点 i, j（0-indexed）を結ぶ辺の重みを D * |i - j| + A_i + A_j とする
// 入力：N D、続いて A_0 … A_{N-1}。出力：最小全域木の重み
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

const long long INF = LLONG_MAX;

// 成分の異なる上位 2 件を保つ（同じ成分の候補が 2 件を占めないようにする）
struct Top2 {
    pair<long long, int> a{INF, -1}, b{INF, -1};  // (値, 頂点)。a が最小
    void add(long long val, int v, const vector<int>& comp) {
        pair<long long, int> c{val, v};
        if (a.second != -1 && comp[a.second] == comp[v]) {
            a = min(a, c);
        } else if (c < a) {
            b = a;
            a = c;
        } else {
            b = min(b, c);  // b が同じ成分でも別の成分でも、小さい方を残せばよい
        }
    }
    // 成分 cv と異なる成分の最良の候補
    pair<long long, int> other(int cv, const vector<int>& comp) const {
        if (a.second != -1 && comp[a.second] != cv) return a;
        return b;
    }
};

// --8<-- [start:core]
long long boruvka(int n, long long d, const vector<long long>& a) {
    atcoder::dsu uf(n);
    vector<int> comp(n);
    long long total = 0;
    int components = n;
    while (components > 1) {
        for (int i = 0; i < n; i++) comp[i] = uf.leader(i);
        // best[c] = 成分 c から外へ出る最小の辺 (重み, 相手の頂点, 自分の頂点)
        vector<tuple<long long, int, int>> best(n, {INF, -1, -1});
        auto relax = [&](int i, pair<long long, int> cand, long long add) {
            if (cand.second == -1) return;
            tuple<long long, int, int> e{cand.first + add, max(i, cand.second), min(i, cand.second)};
            best[comp[i]] = min(best[comp[i]], e);  // 重みが同じなら頂点の組で決める
        };
        Top2 left, right;
        for (int i = 0; i < n; i++) {  // j < i：重み (A_j - D j) + (A_i + D i)
            relax(i, left.other(comp[i], comp), a[i] + d * i);
            left.add(a[i] - d * i, i, comp);
        }
        for (int i = n - 1; i >= 0; i--) {  // j > i：重み (A_j + D j) + (A_i - D i)
            relax(i, right.other(comp[i], comp), a[i] - d * i);
            right.add(a[i] + d * i, i, comp);
        }
        for (int c = 0; c < n; c++) {
            auto [w, u, v] = best[c];
            if (u == -1 || uf.same(u, v)) continue;  // 2 つの成分が同じ辺を選んだときは 1 回だけ
            uf.merge(u, v);
            total += w;
            components--;
        }
    }
    return total;
}
// --8<-- [end:core]

// 素朴な方法：配列のプリム法 O(N^2)
long long prim(int n, long long d, const vector<long long>& a) {
    vector<long long> dist(n, INF);
    vector<bool> used(n, false);
    dist[0] = 0;
    long long total = 0;
    for (int k = 0; k < n; k++) {
        int v = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (v == -1 || dist[i] < dist[v])) v = i;
        used[v] = true;
        total += dist[v];
        for (int i = 0; i < n; i++)
            if (!used[i]) dist[i] = min(dist[i], d * abs(i - v) + a[i] + a[v]);
    }
    return total;
}

int main() {
    int n;
    long long d;
    cin >> n >> d;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long ans = boruvka(n, d, a);
    assert(ans == prim(n, d, a));
    // 乱数で素朴な方法と比べる
    mt19937 rng(1);
    for (int t = 0; t < 300; t++) {
        int m = rng() % 30 + 1;
        long long dd = rng() % 5;
        vector<long long> b(m);
        for (auto& x : b) x = rng() % 6;
        assert(boruvka(m, dd, b) == prim(m, dd, b));
    }
    cout << ans << '\n';
}
