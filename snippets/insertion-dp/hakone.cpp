// 1〜n の順列 p のうち、|p_1 - 1| + … + |p_n - n| がちょうど k になるものの数を
// 10^9+7 で割った余りで求める。位置と値を左から同時に見て、相手が未定の数を状態にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    assert(n >= 1 && k >= 0);
    const long long MOD = 1000000007;
    int kmax = n * n;  // 和は n^2 / 2 を超えない。余裕を見て n^2 まで持つ
    if (k > kmax) {
        cout << 0 << '\n';
        return 0;
    }

    // --8<-- [start:core]
    // dp[d][s] = 位置 1〜t と値 1〜t を見て、相手が未定の位置（＝未定の値）が d 個、
    //            ここまでの寄与の和が s である決め方の数
    vector dp(n + 1, vector<long long>(kmax + 1, 0));
    dp[0][0] = 1;
    for (int t = 0; t < n; t++) {  // 位置 t+1 と値 t+1 を加える
        vector ndp(n + 1, vector<long long>(kmax + 1, 0));
        for (int d = 0; d <= t; d++) {
            for (int s = 0; s <= kmax; s++) {
                long long v = dp[d][s];
                if (v == 0) continue;
                // 遷移後の未定の数 nd が決まると、次の隙間を横切る線は 2 * nd 本
                auto add = [&](int nd, long long coef) {
                    int ns = s + 2 * nd;
                    if (nd < 0 || ns > kmax) return;
                    ndp[nd][ns] = (ndp[nd][ns] + v * coef) % MOD;
                };
                add(d + 1, 1);                    // 位置も値も未定のまま残す
                add(d, 1);                        // 新しい位置と新しい値を結ぶ
                add(d, 2LL * d);                  // 片方だけを未定の相手と結ぶ（位置側・値側）
                add(d - 1, 1LL * d * d % MOD);    // 両方を未定の相手と結ぶ
            }
        }
        dp = ndp;
    }
    cout << dp[0][k] << '\n';
    // --8<-- [end:core]
}
