// 分割点型：隣り合う 2 つを合体させるたびに大きさの和のコストがかかるとき、
// 列 a 全体を 1 つにするコストの最小を求める。dp[l][r] = 半開区間 [l, r) を 1 つにする最小コスト。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(n >= 1);

    // --8<-- [start:core]
    vector<long long> s(n + 1, 0);  // s[i] = a[0] + … + a[i-1]
    for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];

    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, INF));
    for (int l = 0; l < n; l++) dp[l][l + 1] = 0;  // 1 つだけなら合体は要らない

    for (int len = 2; len <= n; len++) {         // 短い区間から順に
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            for (int m = l + 1; m < r; m++) {     // 最後の合体の境目 m
                dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r]);
            }
            dp[l][r] += s[r] - s[l];              // 最後の合体のコストは境目によらない
        }
    }
    cout << dp[0][n] << '\n';
    // --8<-- [end:core]
}
