// 最長共通部分列（LCS）：長さを 2 次元の表で求め、右下から逆にたどって 1 つ復元する。
// 入力：文字列 s と t。出力：LCS の長さと、LCS の 1 つ（空なら空行）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    // --8<-- [start:core]
    // dp[i][j] = s の先頭 i 文字と t の先頭 j 文字の LCS の長さ（0 行目・0 列目は空の列で 0）
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;  // 末尾どうしを組にする
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);           // どちらかの末尾を捨てる
        }
    }

    // 復元：(n, m) から、その値を作った遷移を逆にたどる
    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j]) i--;          // s の末尾を捨てても同じ値
        else if (dp[i][j] == dp[i][j - 1]) j--;     // t の末尾を捨てても同じ値
        else {                                      // 斜めから来た（s[i-1] == t[j-1]）
            lcs.push_back(s[i - 1]);
            i--, j--;
        }
    }
    reverse(lcs.begin(), lcs.end());  // 後ろから集めたので反転する
    // --8<-- [end:core]

    assert((int)lcs.size() == dp[n][m]);
    cout << dp[n][m] << '\n' << lcs << '\n';
}
