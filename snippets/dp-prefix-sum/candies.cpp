// 上限つきの配り方：n 人に k 個を、i 番目の人には 0〜a[i] 個ずつ余さず配る方法の数を
// 10^9+7 で割った余りで求める。前の段の累積和で、区間からの遷移を O(1) にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        assert(0 <= a[i]);
    }
    const long long MOD = 1000000007;

    // --8<-- [start:core]
    // dp[j] = これまでの人に合計 j 個を配る方法の数（1 段分だけ持つ）
    vector<long long> dp(k + 1, 0);
    dp[0] = 1;  // 0 人に 0 個を配る方法は 1 通り
    vector<long long> s(k + 2);
    for (int i = 0; i < n; i++) {
        s[0] = 0;  // s[j] = dp[0] + … + dp[j-1]（前の段の累積和を先に作り切る）
        for (int j = 0; j <= k; j++) s[j + 1] = (s[j] + dp[j]) % MOD;
        for (int j = 0; j <= k; j++) {
            // i 番目の人に c 個（0 ≤ c ≤ a[i]）配ると、前の段の j - c から来る
            int lo = max(0, j - a[i]);  // 半開区間 [lo, j + 1) の和
            dp[j] = (s[j + 1] - s[lo] + MOD) % MOD;
        }
    }
    cout << dp[k] << '\n';
    // --8<-- [end:core]
}
