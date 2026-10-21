// 壁 '#' のあるグリッドで、右・下・右下のどれかへ壁の手前まで何マスでも進めるとき、
// 左上から右下へ行く方法の数を 10^9+7 で割った余りで求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (int i = 0; i < h; i++) cin >> g[i];
    assert(h >= 1 && w >= 1 && g[0][0] == '.');
    const long long MOD = 1000000007;

    // --8<-- [start:core]
    // dp[i][j]：(i, j) で止まる方法の数
    // row[i][j]・col[i][j]・diag[i][j]：(i, j) から左・上・左上へ、壁の手前まで続くマスの dp の和
    //   （(i, j) 自身を含む。壁のマスでは 0 に戻す）
    vector<vector<long long>> dp(h, vector<long long>(w, 0));
    auto row = dp, col = dp, diag = dp;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (g[i][j] == '#') continue;  // 壁：dp も 3 つの和も 0（ここで和が途切れる）
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else {
                long long s = 0;
                if (j > 0) s += row[i][j - 1];           // 左から 1 手で来る
                if (i > 0) s += col[i - 1][j];           // 上から 1 手で来る
                if (i > 0 && j > 0) s += diag[i - 1][j - 1];  // 左上から 1 手で来る
                dp[i][j] = s % MOD;
            }
            row[i][j] = ((j > 0 ? row[i][j - 1] : 0) + dp[i][j]) % MOD;
            col[i][j] = ((i > 0 ? col[i - 1][j] : 0) + dp[i][j]) % MOD;
            diag[i][j] = ((i > 0 && j > 0 ? diag[i - 1][j - 1] : 0) + dp[i][j]) % MOD;
        }
    }
    cout << dp[h - 1][w - 1] << '\n';
    // --8<-- [end:core]
}
