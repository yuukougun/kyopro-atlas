// 頂点の選び方を、選んだ頂点が作る連結成分の数 k ごとに数える（mod 998244353）
// 頂点の状態（選ぶか）と個数（成分の数）を同時に持つ二乗の木 DP
// 入力：N、続く N - 1 行に辺 u v（1-indexed）。出力：k = 1, …, N の個数を 1 行ずつ
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // --8<-- [start:core]
    // dp[v][x][k]：v の部分木で、v を選ぶか（x = 1）選ばないか（x = 0）、成分が k 個の選び方の数
    vector<array<vector<mint>, 2>> dp(n);
    vector<int> sz(n);
    auto dfs = [&](auto&& self, int v, int p) -> void {
        auto& d = dp[v];
        d[0] = {1, 0};  // v を選ばない：成分 0 個が 1 通り
        d[1] = {0, 1};  // v を選ぶ：成分 1 個が 1 通り
        sz[v] = 1;
        for (int c : g[v]) {
            if (c == p) continue;
            self(self, c, v);
            int s = sz[v], t = sz[c];  // 添字の範囲は 0..s と 0..t
            array<vector<mint>, 2> nxt;
            nxt[0].assign(s + t + 1, 0);
            nxt[1].assign(s + t + 1, 0);
            for (int i = 0; i <= s; i++) {
                for (int j = 0; j <= t; j++) {
                    mint c0 = dp[c][0][j], c1 = dp[c][1][j];
                    nxt[0][i + j] += d[0][i] * (c0 + c1);
                    nxt[1][i + j] += d[1][i] * c0;
                    // v も c も選ぶと、2 つの成分が辺 (v, c) でつながって 1 つ減る
                    if (i >= 1 && j >= 1) nxt[1][i + j - 1] += d[1][i] * c1;
                }
            }
            d = move(nxt);
            sz[v] += t;   // サイズはマージの後で足す
            dp[c] = array<vector<mint>, 2>();   // 子の配列はもう使わないので捨てる（メモリを O(N) に保つ）
        }
    };
    dfs(dfs, 0, -1);
    // --8<-- [end:core]
    vector<mint> ans(n + 1);
    for (int k = 1; k <= n; k++) ans[k] = dp[0][0][k] + dp[0][1][k];
    // 小さい木では全通りを試して確かめる
    if (n <= 12) {
        vector<long long> cnt(n + 1, 0);
        for (int m = 1; m < (1 << n); m++) {
            vector<int> seen(n, 0);
            int comp = 0;
            for (int s = 0; s < n; s++) {
                if (!(m >> s & 1) || seen[s]) continue;
                comp++;
                vector<int> st = {s};
                seen[s] = 1;
                while (!st.empty()) {
                    int v = st.back();
                    st.pop_back();
                    for (int c : g[v])
                        if ((m >> c & 1) && !seen[c]) seen[c] = 1, st.push_back(c);
                }
            }
            cnt[comp]++;
        }
        for (int k = 1; k <= n; k++) assert(ans[k].val() == cnt[k]);
    }
    for (int k = 1; k <= n; k++) cout << ans[k].val() << '\n';
}
