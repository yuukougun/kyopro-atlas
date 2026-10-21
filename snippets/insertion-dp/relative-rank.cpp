// 隣り合う大小関係の列 s（'<'・'>'・'?'。'?' は条件なし）を満たす 1〜n の順列の数を
// 10^9+7 で割った余りで求める。最後の要素の相対順位を状態にし、累積和で O(n^2) にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n;
    if (n >= 2) cin >> s;
    assert(n >= 1 && (int)s.size() == n - 1);
    const long long MOD = 1000000007;

    // --8<-- [start:core]
    // dp[j] = 先頭 i 個を決めたとき、最後の要素が i 個の中で j 番目に小さい（0 始まり）並べ方の数
    vector<long long> dp = {1};  // i = 1：1 個だけなら相対順位は 0
    for (int i = 1; i < n; i++) {
        // s[i-1] は i 個目と i+1 個目の関係。前の段の累積和 pre[j] = dp[0] + … + dp[j-1]
        vector<long long> pre(i + 1, 0);
        for (int j = 0; j < i; j++) pre[j + 1] = (pre[j] + dp[j]) % MOD;
        vector<long long> ndp(i + 1);
        for (int k = 0; k <= i; k++) {  // 新しい要素の相対順位 k（i+1 個の中で）
            if (s[i - 1] == '<') {
                ndp[k] = pre[k];  // 前の最後 j が j < k なら、新しい要素の方が大きい
            } else if (s[i - 1] == '>') {
                ndp[k] = (pre[i] - pre[k] + MOD) % MOD;  // j ≥ k なら前の最後の方が大きい
            } else {
                ndp[k] = pre[i];  // 条件なし
            }
        }
        dp = ndp;
    }
    long long ans = 0;
    for (long long x : dp) ans = (ans + x) % MOD;
    cout << ans << '\n';
    // --8<-- [end:core]
}
