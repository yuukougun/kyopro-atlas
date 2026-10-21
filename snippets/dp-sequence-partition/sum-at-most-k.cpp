// 0 以上の整数の列 a を連続する区間に区切り、どの区間の和も K 以下にする区切り方の数を
// 998244353 で割った余りで求める。遷移元の左端の範囲が単調に動くので、尺取りと dp の累積和で O(n)。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (auto& x : a) {
        cin >> x;
        assert(x >= 0);
    }

    // --8<-- [start:core]
    // dp[i] ＝ 先頭 i 個 a[0..i) の区切り方の数。T[i] ＝ dp[0] + … + dp[i-1]
    vector<long long> dp(n + 1, 0), T(n + 2, 0);
    dp[0] = 1;  // 空の列を区切る方法（区間 0 個）が 1 通り
    T[1] = 1;
    int lo = 0;          // 最後の区間 [j, i) の和が K 以下になる最小の j
    long long sum = 0;   // a[lo..i) の和
    for (int i = 1; i <= n; i++) {
        sum += a[i - 1];
        while (lo < i && sum > K) sum -= a[lo++];  // 和が K を超える間は左端を進める
        // 遷移元は j ∈ [lo, i)。lo == i なら a[i-1] だけで K を超えていて 0 通り
        dp[i] = (T[i] - T[lo] + MOD) % MOD;
        T[i + 1] = (T[i] + dp[i]) % MOD;
    }
    // --8<-- [end:core]

    // 素朴に j を全部試す O(n^2) の DP と突き合わせる
    vector<long long> naive(n + 1, 0);
    naive[0] = 1;
    for (int i = 1; i <= n; i++) {
        long long s = 0;
        for (int j = i - 1; j >= 0; j--) {
            s += a[j];
            if (s <= K) naive[i] = (naive[i] + naive[j]) % MOD;
        }
    }
    assert(naive == dp);
    cout << dp[n] << '\n';
}
