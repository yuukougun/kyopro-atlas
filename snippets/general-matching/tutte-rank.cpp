#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 最大マッチングの大きさを、Tutte 行列に乱数を入れた行列の階数の半分として求める。
// 間違える確率は n / 998244353 以下（大きく見積もっても 1 回あたり 10^{-6} ほど）。
// --8<-- [start:core]
int max_matching_size(int n, const vector<pair<int, int>>& edges) {
    mt19937 rng(random_device{}());
    vector<vector<mint>> a(n, vector<mint>(n, 0));
    for (auto [u, v] : edges) {
        mint x = rng() % (mint::mod() - 1) + 1;  // 0 でない乱数
        a[u][v] = x;
        a[v][u] = -x;  // 交代行列（a[v][u] = -a[u][v]）
    }
    int rank = 0;  // 掃き出し法で階数を求める
    for (int col = 0; col < n && rank < n; col++) {
        int piv = -1;
        for (int r = rank; r < n; r++) {
            if (a[r][col] != 0) { piv = r; break; }
        }
        if (piv == -1) continue;
        swap(a[piv], a[rank]);
        mint inv = a[rank][col].inv();
        for (int r = rank + 1; r < n; r++) {
            mint f = a[r][col] * inv;
            if (f == 0) continue;
            for (int c = col; c < n; c++) a[r][c] -= f * a[rank][c];
        }
        rank++;
    }
    return rank / 2;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) cin >> u >> v;
    int ans = max_matching_size(n, edges);
    assert(0 <= ans && 2 * ans <= n);
    cout << ans << '\n';
}
