// N ≤ 8 の重み付き連結グラフで、全域木の重みの和を K で割った余りの最小値を、N-1 本の辺の組の全列挙で求める
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

// --8<-- [start:core]
long long min_tree_mod(int n, const vector<Edge>& edges, long long k) {
    int m = edges.size();
    vector<int> sel(m, 0);
    fill(sel.end() - (n - 1), sel.end(), 1);     // 0…0 1…1（昇順）から始めると C(M, N-1) 通りを全部回る
    long long best = LLONG_MAX;  // 最小値を取るだけで足さないのでこの値でよい
    do {
        vector<int> par(n);
        iota(par.begin(), par.end(), 0);
        auto find = [&](auto&& self, int x) -> int { return par[x] == x ? x : par[x] = self(self, par[x]); };
        bool tree = true;
        long long sum = 0;
        for (int e = 0; e < m && tree; e++) {
            if (!sel[e]) continue;
            int a = find(find, edges[e].u), b = find(find, edges[e].v);
            if (a == b) tree = false;            // 閉路ができた：N-1 本で閉路があれば全域木でない
            par[a] = b;
            sum = (sum + edges[e].w) % k;        // 和は大きくなりうるので毎回余りをとる
        }
        if (tree) best = min(best, sum);
    } while (next_permutation(sel.begin(), sel.end()));
    return best;
}
// --8<-- [end:core]

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    assert(2 <= n && n <= 8 && n - 1 <= m && m <= n * (n - 1) / 2);
    vector<Edge> edges(m);
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        u--, v--;                                // 入力は 1-indexed
    }
    cout << min_tree_mod(n, edges, k) << '\n';
}
