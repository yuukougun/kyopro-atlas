// 貰う形＋累積和：歩幅の集合が k 個の閉区間 [l_t, r_t] の和集合のとき、
// マス 0 からマス n-1 まで進む方法の数を 998244353 で割った余りで求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> l(k), r(k);
    for (int t = 0; t < k; t++) {
        cin >> l[t] >> r[t];
        assert(1 <= l[t] && l[t] <= r[t]);
    }
    const long long MOD = 998244353;

    // --8<-- [start:core]
    vector<long long> dp(n, 0);
    vector<long long> s(n + 1, 0);  // s[i] = dp[0] + … + dp[i-1]（半開区間 [0, i) の和）
    for (int i = 0; i < n; i++) {
        if (i == 0) dp[i] = 1;      // 初期値：マス 0 にいる方法は 1 通り
        for (int t = 0; t < k; t++) {
            // 遷移元は閉区間 [i - r, i - l]、すなわち半開区間 [i - r, i - l + 1)
            int lo = max(0, i - r[t]);
            int hi = i - l[t] + 1;  // l >= 1 なので hi <= i で、s[hi] は計算済み
            if (hi <= lo) continue;  // 空区間
            dp[i] = (dp[i] + s[hi] - s[lo] + MOD) % MOD;  // 差が負にならないよう MOD を足す
        }
        s[i + 1] = (s[i] + dp[i]) % MOD;  // dp[i] が確定してから累積和を伸ばす
    }
    cout << dp[n - 1] << '\n';
    // --8<-- [end:core]
}
