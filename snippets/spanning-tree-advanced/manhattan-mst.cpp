// Manhattan MST：マンハッタン距離を重みにした完全グラフの最小全域木
// 入力：N、続く N 行は「x y」。出力：最小全域木の重み
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

struct Edge {
    long long w;
    int u, v;
};

// --8<-- [start:core]
// 最小全域木を含む候補の辺（高々 4N 本）を返す
vector<Edge> manhattan_candidates(vector<long long> x, vector<long long> y) {
    int n = x.size();
    vector<Edge> edges;
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    for (int k = 0; k < 4; k++) {
        // 各点 j について、0 ≤ (y の差) ≤ (x の差) の領域で最も近い点を探す。
        // その領域では距離が (x_i + y_i) - (x_j + y_j) なので、x + y の小さい順に見て最初に来た点が答え
        sort(id.begin(), id.end(), [&](int i, int j) { return x[i] + y[i] < x[j] + y[j]; });
        map<long long, int> sweep;  // キーは -y（y の大きい順）。まだ相手の決まっていない点
        for (int i : id) {
            for (auto it = sweep.lower_bound(-y[i]); it != sweep.end(); it = sweep.erase(it)) {
                int j = it->second;  // y_j ≤ y_i
                long long dx = x[i] - x[j], dy = y[i] - y[j];
                if (dy > dx) break;  // 領域の外。これより y の小さい点も外
                edges.push_back({dx + dy, i, j});  // j にとって i が領域内で最も近い点
            }
            sweep[-y[i]] = i;
        }
        // 座標を変換して 4 つの向きを順に調べる（x と y の交換、x の符号の反転）
        if (k % 2 == 0) swap(x, y);
        else for (auto& v : x) v = -v;
    }
    return edges;
}
// --8<-- [end:core]

long long kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    atcoder::dsu d(n);
    long long total = 0;
    for (const auto& [w, u, v] : edges) {
        if (d.same(u, v)) continue;
        d.merge(u, v);
        total += w;
    }
    return total;
}

// 素朴な方法：すべての点対の辺でクラスカル法
long long brute(const vector<long long>& x, const vector<long long>& y) {
    int n = x.size();
    vector<Edge> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) edges.push_back({llabs(x[i] - x[j]) + llabs(y[i] - y[j]), i, j});
    return kruskal(n, edges);
}

int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    auto cand = manhattan_candidates(x, y);
    assert((int)cand.size() <= 4 * n);
    long long ans = kruskal(n, cand);
    assert(ans == brute(x, y));
    // 乱数で素朴な方法と比べる（同じ座標の点も含める）
    mt19937 rng(1);
    for (int t = 0; t < 500; t++) {
        int m = rng() % 25 + 1;
        vector<long long> a(m), b(m);
        for (int i = 0; i < m; i++) a[i] = rng() % 8, b[i] = rng() % 8;
        assert(kruskal(m, manhattan_candidates(a, b)) == brute(a, b));
    }
    cout << ans << '\n';
}
