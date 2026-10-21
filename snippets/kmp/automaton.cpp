// 照合オートマトンの表と、P を含まない長さ L の英小文字列の数（mod 998244353）
// 入力：P L（P は英小文字で空でない、0 ≤ L）。出力：個数
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// --8<-- [start:core]
// nxt[j][c] = 状態 j（末尾が P[0, j) と一致）で文字 c を読んだ後の状態（0 ≤ j ≤ m）
vector<array<int, 26>> build_automaton(const string& p) {
    int m = p.size();
    vector<int> pi = prefix_function(p);
    vector<array<int, 26>> nxt(m + 1);
    for (int j = 0; j <= m; j++) {
        for (int c = 0; c < 26; c++) {
            if (j < m && p[j] - 'a' == c) nxt[j][c] = j + 1;  // 一致して伸びる
            else if (j == 0) nxt[j][c] = 0;
            else nxt[j][c] = nxt[pi[j - 1]][c];                // border の状態の行を写す
        }
    }
    return nxt;
}
// --8<-- [end:core]

int main() {
    string p;
    int len;
    cin >> p >> len;
    int m = p.size();
    auto nxt = build_automaton(p);
    // --8<-- [start:dp]
    vector<mint> dp(m + 1, 0);                   // dp[j] = いまの状態が j の文字列の数
    dp[0] = 1;
    for (int step = 0; step < len; step++) {
        vector<mint> ndp(m + 1, 0);
        for (int j = 0; j < m; j++) {            // 状態 m（P を含んだ）には入れない
            for (int c = 0; c < 26; c++) {
                int k = nxt[j][c];
                if (k < m) ndp[k] += dp[j];
            }
        }
        dp = ndp;
    }
    mint ans = 0;
    for (int j = 0; j < m; j++) ans += dp[j];
    // --8<-- [end:dp]
    cout << ans.val() << '\n';
}
