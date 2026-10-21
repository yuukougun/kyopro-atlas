// 1 以上 N 以下の整数のうち、各桁の和で割り切れるものの個数
// 入力：N（1 ≤ N ≤ 10^14）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_divisible(long long n) {
    string s = to_string(n);
    int len = s.size();
    long long res = 0;
    for (int m = 1; m <= 9 * len; m++) {  // 桁和を m と決め打つ
        // dp[t][sum][r]：N と一致しているか、ここまでの桁和、ここまでの数を m で割った余り
        vector dp(2, vector(m + 1, vector<long long>(m, 0)));
        dp[1][0][0] = 1;
        for (int i = 0; i < len; i++) {
            int lim = s[i] - '0';
            vector nd(2, vector(m + 1, vector<long long>(m, 0)));
            for (int t = 0; t < 2; t++) {
                for (int sum = 0; sum <= m; sum++) {
                    for (int r = 0; r < m; r++) {
                        if (dp[t][sum][r] == 0) continue;
                        int hi = t ? lim : 9;
                        for (int x = 0; x <= hi && sum + x <= m; x++) {  // 桁和が m を超えたら捨てる
                            int nt = (t && x == lim) ? 1 : 0;
                            nd[nt][sum + x][(r * 10 + x) % m] += dp[t][sum][r];
                        }
                    }
                }
            }
            dp = nd;
        }
        res += dp[0][m][0] + dp[1][m][0];  // 桁和がちょうど m で、m で割り切れる
    }
    return res;
}
// --8<-- [end:core]

long long brute(int n) {
    long long res = 0;
    for (int x = 1; x <= n; x++) {
        int sum = 0;
        for (int y = x; y > 0; y /= 10) sum += y % 10;
        if (x % sum == 0) res++;
    }
    return res;
}

int main() {
    for (int n = 1; n <= 300; n++) assert(count_divisible(n) == brute(n));
    long long n;
    cin >> n;
    cout << count_divisible(n) << '\n';
}
