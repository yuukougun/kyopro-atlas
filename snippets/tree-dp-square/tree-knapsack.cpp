// 木の上のナップサック：頂点 0 を根とし、「選んだ頂点の親も選ぶ」ように
// ちょうど K 頂点を選んだときの重みの和の最大。配列の長さを min(部分木のサイズ, K) + 1 に抑える
// 入力：N K、重み a_1 … a_N、続く N - 1 行に辺 u v（1-indexed）。1 ≤ K ≤ N
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, K;
    cin >> n >> K;
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
    // --8<-- [start:core]
    const long long NEG = LLONG_MIN / 4;  // 作れない個数の印
    // 返す配列 dp[k]：v の部分木から、v を含み親へ閉じた k 頂点を選んだときの重みの和の最大
    // （k = 0 は v を選ばず、部分木から何も選ばない）。2 つ目の値は部分木のサイズ
    auto dfs = [&](auto&& self, int v, int p) -> pair<vector<long long>, int> {
        vector<long long> cur = {0, a[v]};  // 長さ min(s, K) + 1
        int s = 1;                          // マージ済みの頂点の数（v を含む）
        for (int c : g[v]) {
            if (c == p) continue;
            auto [child, t] = self(self, c, v);
            vector<long long> nxt(min(s + t, K) + 1, NEG);
            nxt[0] = 0;
            for (int i = 1; i <= min(s, K); i++) {      // v は選ぶ（i ≥ 1）
                if (cur[i] == NEG) continue;
                for (int j = 0; j <= min(t, K - i); j++) {  // 子の側から j 頂点
                    if (child[j] == NEG) continue;
                    nxt[i + j] = max(nxt[i + j], cur[i] + child[j]);
                }
            }
            cur = move(nxt);
            s += t;  // サイズはマージの後で足す
        }
        return {cur, s};
    };
    auto [dp, sz] = dfs(dfs, 0, -1);
    long long ans = dp[K];
    // --8<-- [end:core]
    // 小さい木では全通りを試して確かめる
    if (n <= 15) {
        vector<int> par(n, -1), order = {0};
        for (int i = 0; i < (int)order.size(); i++) {
            int v = order[i];
            for (int c : g[v])
                if (c != par[v]) par[c] = v, order.push_back(c);
        }
        long long best = NEG;
        for (int m = 0; m < (1 << n); m++) {
            if (__builtin_popcount(m) != K || !(m & 1)) continue;
            bool ok = true;
            long long sum = 0;
            for (int v = 0; v < n; v++) {
                if (!(m >> v & 1)) continue;
                sum += a[v];
                if (v != 0 && !(m >> par[v] & 1)) ok = false;
            }
            if (ok) best = max(best, sum);
        }
        assert(ans == best);
    }
    assert(sz == n);
    cout << ans << '\n';
}
