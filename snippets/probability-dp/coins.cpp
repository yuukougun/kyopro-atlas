// N 枚のコインを順に投げ、i 枚目は確率 p[i] で表が出る。表の枚数が裏の枚数より多くなる確率を求める。
// 表の枚数ごとの確率を、0 枚投げた時点の「表 0 枚が確率 1」から前へ配る。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 戻り値の dp[j] = N 枚すべて投げた後に、表がちょうど j 枚である確率
vector<double> heads_distribution(const vector<double>& p) {
    int n = p.size();
    vector<double> dp(n + 1, 0.0);
    dp[0] = 1.0;  // 0 枚投げた時点では「表 0 枚」が確率 1
    for (int i = 0; i < n; i++) {
        vector<double> nxt(n + 1, 0.0);  // 次の時刻の表は別の配列に作る
        for (int j = 0; j <= i; j++) {
            nxt[j + 1] += dp[j] * p[i];      // i 枚目が表
            nxt[j] += dp[j] * (1.0 - p[i]);  // i 枚目が裏
        }
        dp = move(nxt);
        double total = accumulate(dp.begin(), dp.end(), 0.0);
        assert(abs(total - 1.0) < 1e-9);  // 検算：確率の和は 1 のまま
    }
    return dp;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<double> p(n);
    for (auto& x : p) cin >> x;
    vector<double> dp = heads_distribution(p);
    double ans = 0.0;
    for (int j = 0; j <= n; j++) {
        if (2 * j > n) ans += dp[j];  // 表 j 枚・裏 n - j 枚で、表の方が多い
    }
    cout << fixed << setprecision(10) << ans << '\n';
}
