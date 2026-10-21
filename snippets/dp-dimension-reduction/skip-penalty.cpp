// 点 0, 1, …, N-1 を順に回る。途中の点を飛ばしてよく、飛ばした数 C が 1 以上なら 2^(C-1) のペナルティがかかる。
// 移動距離とペナルティの和の最小を求める。座標は 0 以上 10^4 以下、N は 10^4 以下とする。
// 飛ばさない経路の距離は 1.5×10^8 < 2^28 未満なので、C は 28 までだけを添字にすれば足りる。
// 小さい N では全探索の答えと突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    auto dist = [&](int i, int j) { return hypot(x[i] - x[j], y[i] - y[j]); };

    // --8<-- [start:core]
    const int CMAX = 28;  // 2^(C-1) >= 2^28 になる C は、飛ばさない経路より必ず悪い
    const double INF = 1e18;
    // dp[i][c]：点 i を通った（飛ばしていない）時点で、それまでに c 個飛ばしたときの距離の最小
    vector<vector<double>> dp(n, vector<double>(CMAX + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
        // 直前に通った点 j から i へ。間の i - j - 1 個を飛ばす
        for (int j = max(0, i - 1 - CMAX); j < i; j++) {
            int skip = i - j - 1;
            for (int c = 0; c + skip <= CMAX; c++) {
                dp[i][c + skip] = min(dp[i][c + skip], dp[j][c] + dist(j, i));
            }
        }
    }
    double ans = INF;
    for (int c = 0; c <= CMAX; c++) {
        double penalty = (c == 0 ? 0 : pow(2.0, c - 1));
        ans = min(ans, dp[n - 1][c] + penalty);
    }
    cout << fixed << setprecision(6) << ans << '\n';
    // --8<-- [end:core]

    if (n <= 15) {  // 通る点の集合を全探索して確かめる（両端は必ず通る）
        double best = INF;
        for (int s = 0; s < (1 << n); s++) {
            if (!(s & 1) || !(s >> (n - 1) & 1)) continue;
            double d = 0;
            int prev = 0, c = 0;
            for (int i = 1; i < n; i++) {
                if (s >> i & 1) {
                    d += dist(prev, i);
                    prev = i;
                } else {
                    c++;
                }
            }
            best = min(best, d + (c == 0 ? 0 : pow(2.0, c - 1)));
        }
        assert(abs(best - ans) < 1e-6);
    }
}
