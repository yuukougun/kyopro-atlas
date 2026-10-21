#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

// --8<-- [start:core]
// s から文字を選び、元の順に並べると t になる選び方の数
mint count_subsequence(const string& s, const string& t) {
    int m = t.size();
    vector<mint> dp(m + 1);  // dp[j]：t の先頭 j 文字まで集めた選び方の数
    dp[0] = 1;
    for (char c : s) {
        // j の大きい方から：同じ文字で 2 段進まないように
        for (int j = m - 1; j >= 0; j--) {
            if (c == t[j]) dp[j + 1] += dp[j];
        }
    }
    return dp[m];
}
// --8<-- [end:core]

long long brute(const string& s, const string& t) {
    int n = s.size();
    long long cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        string u;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) u += s[i];
        }
        if (u == t) cnt++;
    }
    return cnt;
}

int main() {
    string s, t;
    cin >> s >> t;
    mint ans = count_subsequence(s, t);
    if (s.size() <= 16) assert(ans.val() == brute(s, t) % 1000000007);
    cout << ans.val() << '\n';
}
