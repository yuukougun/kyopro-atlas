// 端の相手で分ける数え上げ：2n 人が一列に並ぶ。組んでよい 2 人の組が m 個与えられる。
// 隣り合う 2 人を組にして列から取り除く操作を n 回行い、全員を取り除く操作の列の数を 998244353 で割った余りを求める。
// dp[l][r] = 半開区間 [l, r) の人だけで、全員を取り除く操作の列の数（r - l は偶数）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> ok(2 * n, vector<bool>(2 * n, false));
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;  // 0-indexed
        assert(0 <= x && x < y && y < 2 * n);
        ok[x][y] = ok[y][x] = true;
    }

    // --8<-- [start:core]
    int len_max = 2 * n;
    // 二項係数 C[i][j]（i ≤ n）をパスカルの三角形で前計算する
    vector<vector<mint>> C(n + 1, vector<mint>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }

    vector<vector<mint>> dp(len_max + 1, vector<mint>(len_max + 1, 0));
    for (int l = 0; l <= len_max; l++) dp[l][l] = 1;  // 空の区間の取り除き方は 1 通り

    for (int len = 2; len <= len_max; len += 2) {
        for (int l = 0; l + len <= len_max; l++) {
            int r = l + len;
            int k = len / 2;  // [l, r) で行う操作の回数
            // 左端 l と組む相手 p で分ける（p ごとに操作の列が重ならない）
            for (int p = l + 1; p < r; p += 2) {
                if (!ok[l][p]) continue;
                int b = (r - p - 1) / 2;  // 外側 [p+1, r) の操作の回数
                // 内側と組 (l, p) の操作（内側が先、組が最後）と、外側の操作を混ぜる
                dp[l][r] += dp[l + 1][p] * dp[p + 1][r] * C[k][b];
            }
        }
    }
    cout << dp[0][len_max].val() << '\n';
    // --8<-- [end:core]
}
