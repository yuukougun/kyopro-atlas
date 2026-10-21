#include <bits/stdc++.h>
using namespace std;

// 'A'・'B'・'?' からなる S の '?' を埋める方法のうち、
// 長さ K の回文を部分文字列に含まないものの数（mod 998244353）
const long long MOD = 998244353;

// --8<-- [start:core]
long long count_avoid(const string& s, int k) {
    int n = s.size();
    // 状態：末尾の min(i, K-1) 文字。'B' を 1 とする bit で、新しい文字ほど下位
    int w = k - 1;
    int full = 1 << w;
    auto is_pal = [&](int bits, int len) {  // 下位 len bit が回文か
        for (int a = 0, b = len - 1; a < b; a++, b--) {
            if (((bits >> a) & 1) != ((bits >> b) & 1)) return false;
        }
        return true;
    };
    vector<long long> dp(full, 0);
    dp[0] = 1;  // 長さ 0 では末尾の文字がない（短いうちは上位の bit を 0 で埋める）
    for (int i = 0; i < n; i++) {
        vector<long long> ndp(full, 0);
        for (int st = 0; st < full; st++) {
            if (dp[st] == 0) continue;
            for (int c = 0; c < 2; c++) {
                if (s[i] != '?' && s[i] - 'A' != c) continue;
                int win = (st << 1) | c;            // 末尾 K 文字の候補
                if (i + 1 >= k && is_pal(win, k)) continue;  // K 文字そろって回文なら捨てる
                int nst = win & (full - 1);         // 古い 1 文字を落とす
                ndp[nst] = (ndp[nst] + dp[st]) % MOD;
            }
        }
        dp = move(ndp);
    }
    long long ans = 0;
    for (long long v : dp) ans = (ans + v) % MOD;
    return ans;
}
// --8<-- [end:core]

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    assert((int)s.size() == n && 2 <= k && k <= n);
    cout << count_avoid(s, k) << '\n';
}
