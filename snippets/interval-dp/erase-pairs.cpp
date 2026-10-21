// 最後の操作で分ける型：長さが偶数の列 a から、隣り合う 2 つを取り除く操作を繰り返して全部消す。
// 取り除く 2 つの差の絶対値の和の最小を求める。
// dp[l][r] = 半開区間 [l, r) を全部消すときのコストの最小（r - l は偶数）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(n % 2 == 0);

    // --8<-- [start:core]
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, INF));
    for (int l = 0; l <= n; l++) dp[l][l] = 0;  // 空の区間は何もしなくてよい

    for (int len = 2; len <= n; len += 2) {      // 長さが偶数の区間だけ
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            // 左端 a[l] と一緒に消える相手 a[m] で分ける。
            // 内側 [l+1, m) を先に全部消すと a[l] と a[m] が隣り合う。外側 [m+1, r) は独立
            for (int m = l + 1; m < r; m += 2) {
                long long v = dp[l + 1][m] + abs(a[l] - a[m]) + dp[m + 1][r];
                dp[l][r] = min(dp[l][r], v);
            }
        }
    }
    cout << dp[0][n] << '\n';
    // --8<-- [end:core]
}
