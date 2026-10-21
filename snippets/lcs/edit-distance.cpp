// 編集距離（レーベンシュタイン距離）：1 文字の挿入・削除・置換をそれぞれコスト 1 として、
// s を t に変える最小の操作回数を求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    // --8<-- [start:core]
    // dp[i][j] = s の先頭 i 文字を t の先頭 j 文字に変える最小の操作回数
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;  // i 文字を全部削除する
    for (int j = 0; j <= m; j++) dp[0][j] = j;  // j 文字を全部挿入する
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int del = dp[i - 1][j] + 1;                              // s[i-1] を削除
            int ins = dp[i][j - 1] + 1;                              // t[j-1] を挿入
            int sub = dp[i - 1][j - 1] + (s[i - 1] != t[j - 1] ? 1 : 0);  // 一致なら 0、違えば置換
            dp[i][j] = min({del, ins, sub});
        }
    }
    // --8<-- [end:core]

    cout << dp[n][m] << '\n';
}
