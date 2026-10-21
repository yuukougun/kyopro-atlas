// マス 0 から出発し、1 回に L 以上 R 以下だけ進む。ちょうどマス n-1 に着く進み方の数を
// 998244353 で割った余りで求める。遷移元が区間になるので、dp の累積和でまとめて O(n) にする。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int n, L, R;
    cin >> n >> L >> R;
    assert(n >= 1 && 1 <= L && L <= R);

    // --8<-- [start:core]
    // dp[i] ＝ マス i にちょうど着く進み方の数。S[i] ＝ dp[0] + … + dp[i-1]
    vector<long long> dp(n, 0), S(n + 1, 0);
    dp[0] = 1;  // 何もしない進み方が 1 通り
    S[1] = 1;
    for (int i = 1; i < n; i++) {
        // 遷移元は閉区間 [i-R, i-L] ＝ 半開区間 [max(0, i-R), i-L+1)
        int lo = max(0, i - R), hi = i - L + 1;
        if (lo < hi) dp[i] = (S[hi] - S[lo] + MOD) % MOD;  // 引き算の後に MOD を足して負を防ぐ
        S[i + 1] = (S[i] + dp[i]) % MOD;
    }
    // --8<-- [end:core]

    // 素朴に遷移元を 1 つずつ足す O(n (R - L)) の DP と突き合わせる
    vector<long long> naive(n, 0);
    naive[0] = 1;
    for (int i = 1; i < n; i++) {
        for (int d = L; d <= R && d <= i; d++) naive[i] = (naive[i] + naive[i - d]) % MOD;
    }
    assert(naive == dp);
    cout << dp[n - 1] << '\n';
}
