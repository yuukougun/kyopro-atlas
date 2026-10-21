// 1 以上 K 以下の整数のうち、各桁の和が D の倍数になるものの個数を 10^9+7 で割った余り
// 入力：K（10 進の文字列。先頭は 0 でない）D
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// --8<-- [start:core]
long long count_digit_sum(const string& k, int d) {
    // dp[t][r]：上から i 桁を決めた数のうち、
    //   t = 1 ならここまで K と一致、t = 0 なら K より小さいことが確定していて、
    //   桁和を d で割った余りが r のものの個数
    vector dp(2, vector<long long>(d, 0));
    dp[1][0] = 1;  // 何も決めていない数は K と一致している
    for (char c : k) {
        int lim = c - '0';
        vector nd(2, vector<long long>(d, 0));
        for (int t = 0; t < 2; t++) {
            for (int r = 0; r < d; r++) {
                if (dp[t][r] == 0) continue;
                int hi = t ? lim : 9;  // 一致していれば K の桁まで、未満なら 9 まで
                for (int x = 0; x <= hi; x++) {
                    int nt = (t && x == lim) ? 1 : 0;  // K の桁と同じ数字を選んだときだけ一致が続く
                    int nr = (r + x) % d;
                    nd[nt][nr] = (nd[nt][nr] + dp[t][r]) % MOD;
                }
            }
        }
        dp = nd;
    }
    // 0 も「桁和 0」として数えているので 1 を引く
    return (dp[0][0] + dp[1][0] - 1 + MOD) % MOD;
}
// --8<-- [end:core]

long long brute(int k, int d) {
    long long res = 0;
    for (int x = 1; x <= k; x++) {
        int s = 0;
        for (int y = x; y > 0; y /= 10) s += y % 10;
        if (s % d == 0) res++;
    }
    return res;
}

int main() {
    for (int k = 1; k <= 300; k++) {
        for (int d = 1; d <= 12; d++) assert(count_digit_sum(to_string(k), d) == brute(k, d));
    }
    string k;
    int d;
    cin >> k >> d;
    cout << count_digit_sum(k, d) << '\n';
}
