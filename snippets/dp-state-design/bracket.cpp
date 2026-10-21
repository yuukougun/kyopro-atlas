#include <bits/stdc++.h>
using namespace std;

// '('・')'・'?' からなる S の '?' を埋めて正しい括弧列にする方法の数（mod 998244353）
const long long MOD = 998244353;

// --8<-- [start:core]
long long count_brackets(const string& s) {
    int n = s.size();
    // dp[d] ＝ ここまでで、閉じていない '(' が d 個残っている埋め方の数
    vector<long long> dp(n + 2, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        vector<long long> ndp(n + 2, 0);
        for (int d = 0; d <= i; d++) {
            if (dp[d] == 0) continue;
            if (s[i] != ')') ndp[d + 1] = (ndp[d + 1] + dp[d]) % MOD;  // '(' を置く
            if (s[i] != '(' && d > 0) ndp[d - 1] = (ndp[d - 1] + dp[d]) % MOD;  // ')' は d > 0 のときだけ
        }
        dp = move(ndp);
    }
    return dp[0];  // 最後に開き括弧が残っていない
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    cout << count_brackets(s) << '\n';
}
