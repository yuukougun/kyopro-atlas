// 1 以上 N 以下の整数のうち、10 進表記に 0 がちょうど K 個あるものの個数
// 入力：N（1 ≤ N ≤ 10^18）K
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_zeros(long long n, int k) {
    string s = to_string(n);
    int len = s.size();
    if (k > len) return 0;
    // dp[t][z][c]：t は N と一致しているか、z は 0 でない数字をもう置いたか（数が始まったか）、
    //   c は数が始まってから置いた 0 の個数
    vector dp(2, vector(2, vector<long long>(len + 1, 0)));
    dp[1][0][0] = 1;
    for (int i = 0; i < len; i++) {
        int lim = s[i] - '0';
        vector nd(2, vector(2, vector<long long>(len + 1, 0)));
        for (int t = 0; t < 2; t++) {
            for (int z = 0; z < 2; z++) {
                for (int c = 0; c <= len; c++) {
                    if (dp[t][z][c] == 0) continue;
                    int hi = t ? lim : 9;
                    for (int x = 0; x <= hi; x++) {
                        int nt = (t && x == lim) ? 1 : 0;
                        int nz = (z || x != 0) ? 1 : 0;
                        int nc = c + ((z && x == 0) ? 1 : 0);  // 先頭の 0 は数えない
                        nd[nt][nz][nc] += dp[t][z][c];
                    }
                }
            }
        }
        dp = nd;
    }
    long long res = 0;
    for (int t = 0; t < 2; t++) res += dp[t][1][k];  // z = 0（全部 0、すなわち整数の 0）は除く
    return res;
}
// --8<-- [end:core]

long long brute(int n, int k) {
    long long res = 0;
    for (int x = 1; x <= n; x++) {
        string s = to_string(x);
        if (count(s.begin(), s.end(), '0') == k) res++;
    }
    return res;
}

int main() {
    for (int n = 1; n <= 2000; n++) {
        for (int k = 0; k <= 4; k++) assert(count_zeros(n, k) == brute(n, k));
    }
    long long n;
    int k;
    cin >> n >> k;
    cout << count_zeros(n, k) << '\n';
}
