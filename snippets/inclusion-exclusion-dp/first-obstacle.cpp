// H × W のグリッドを左上 (0, 0) から右下 (H-1, W-1) へ右と下だけで進み、
// N 個の障害物のマスを通らない経路の数を 1000000007 で割った余り。
// 入力のマスは 1-indexed。マスの数が小さいときは、表を埋める DP で検算する。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

int main() {
    int h, w, n;
    cin >> h >> w >> n;
    vector<pair<int, int>> obs(n);
    for (auto& [r, c] : obs) {
        cin >> r >> c;
        r--, c--;  // 0-indexed に直す
    }
    int m = h + w;
    vector<mint> fact(m + 1), ifact(m + 1);
    fact[0] = 1;
    for (int i = 1; i <= m; i++) fact[i] = fact[i - 1] * i;
    ifact[m] = fact[m].inv();
    for (int i = m; i >= 1; i--) ifact[i - 1] = ifact[i] * i;

    // --8<-- [start:core]
    // (r1, c1) から (r2, c2) へ右と下だけで行く経路の数。行けなければ 0
    auto paths = [&](pair<int, int> a, pair<int, int> b) -> mint {
        int dr = b.first - a.first, dc = b.second - a.second;
        if (dr < 0 || dc < 0) return 0;
        return fact[dr + dc] * ifact[dr] * ifact[dc];
    };
    // 行・列の辞書順に並べると、j から i へ行けるなら j < i になる
    sort(obs.begin(), obs.end());
    obs.push_back({h - 1, w - 1});  // 終点を最後の「障害物」として足す
    int k = obs.size();
    // dp[i] = 始点から障害物 i へ、ほかの障害物を通らずに行く経路の数
    vector<mint> dp(k);
    for (int i = 0; i < k; i++) {
        dp[i] = paths({0, 0}, obs[i]);
        for (int j = 0; j < i; j++) {
            dp[i] -= dp[j] * paths(obs[j], obs[i]);  // 最初に通る障害物が j の経路を引く
        }
    }
    mint ans = dp[k - 1];
    // --8<-- [end:core]

    if ((long long)h * w <= 400) {
        set<pair<int, int>> wall(obs.begin(), obs.end() - 1);
        vector<vector<mint>> g(h, vector<mint>(w));
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                if (wall.count({r, c})) continue;
                if (r == 0 && c == 0) g[r][c] = 1;
                if (r > 0) g[r][c] += g[r - 1][c];
                if (c > 0) g[r][c] += g[r][c - 1];
            }
        }
        assert(ans == g[h - 1][w - 1]);
    }
    cout << ans.val() << '\n';
}
