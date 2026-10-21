// 壁 '#' のあるグリッドを右か下にだけ進み、左上から右下へ行く経路の数を 10^9+7 で割った余りで求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (int i = 0; i < h; i++) cin >> g[i];
    assert(h >= 1 && w >= 1);
    const long long MOD = 1000000007;

    // --8<-- [start:core]
    // dp[i][j]：左上 (0, 0) からマス (i, j) へ行く経路の数
    vector<vector<long long>> dp(h, vector<long long>(w, 0));
    for (int i = 0; i < h; i++) {        // 行の昇順、行の中は列の昇順
        for (int j = 0; j < w; j++) {    // → 上 (i-1, j) と左 (i, j-1) は計算済み
            if (g[i][j] == '#') {        // 壁には着けない（0 のまま）
                dp[i][j] = 0;
                continue;
            }
            if (i == 0 && j == 0) {      // 出発点：何もしない経路が 1 本
                dp[i][j] = 1;
                continue;
            }
            long long s = 0;
            if (i > 0) s += dp[i - 1][j];  // 1 行目には上がない
            if (j > 0) s += dp[i][j - 1];  // 1 列目には左がない
            dp[i][j] = s % MOD;
        }
    }
    cout << dp[h - 1][w - 1] << '\n';
    // --8<-- [end:core]
}
