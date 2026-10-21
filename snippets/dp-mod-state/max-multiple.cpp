// 個数と余りを状態に持つ：N 個の非負整数からちょうど K 個を選び、和が D の倍数になるときの和の最大を求める。
// そのような選び方がなければ -1 を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, d;
    cin >> n >> k >> d;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(1 <= k && k <= n && 1 <= d);
    for (int i = 0; i < n; i++) assert(a[i] >= 0);

    // --8<-- [start:core]
    const long long NEG = LLONG_MIN;  // 到達できない状態の印
    // dp[j][r] ＝ ここまでの要素から j 個を選び、和を d で割った余りが r のときの和の最大
    vector dp(k + 1, vector<long long>(d, NEG));
    dp[0][0] = 0;  // 何も選ばない：0 個で和 0
    for (int i = 0; i < n; i++) {
        int ai = a[i] % d;  // 余りの計算に使うのは a[i] mod d だけ
        for (int j = min(i, k - 1); j >= 0; j--) {  // j を大きい方から回すと a[i] を 2 回使わない
            for (int r = 0; r < d; r++) {
                if (dp[j][r] == NEG) continue;
                int nr = (r + ai) % d;
                dp[j + 1][nr] = max(dp[j + 1][nr], dp[j][r] + a[i]);  // 値は本当の和（mod を取らない）
            }
        }
    }
    cout << (dp[k][0] == NEG ? -1 : dp[k][0]) << '\n';
    // --8<-- [end:core]
}
