// 0 <= x <= A、0 <= y <= B で、x AND y = 0 となる組 (x, y) の個数
// 入力：A B（どちらも 0 以上 10^11 以下。答えが long long に収まる範囲）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_pairs(long long a, long long b) {
    // dp[tx][ty]：上の bit から決めた途中の (x, y) のうち、
    //   tx = 1 なら x が A と一致、ty = 1 なら y が B と一致しているものの個数
    long long dp[2][2] = {};
    dp[1][1] = 1;
    for (int k = 40; k >= 0; k--) {  // 10^11 < 2^37
        int la = (a >> k) & 1, lb = (b >> k) & 1;
        long long nd[2][2] = {};
        for (int tx = 0; tx < 2; tx++) {
            for (int ty = 0; ty < 2; ty++) {
                if (dp[tx][ty] == 0) continue;
                for (int bx = 0; bx <= (tx ? la : 1); bx++) {
                    for (int by = 0; by <= (ty ? lb : 1); by++) {
                        if (bx & by) continue;  // 同じ bit に 1 が重なる組は捨てる
                        // フラグは数ごとに別々に更新する
                        int ntx = (tx && bx == la) ? 1 : 0;
                        int nty = (ty && by == lb) ? 1 : 0;
                        nd[ntx][nty] += dp[tx][ty];
                    }
                }
            }
        }
        memcpy(dp, nd, sizeof(dp));
    }
    return dp[0][0] + dp[0][1] + dp[1][0] + dp[1][1];
}
// --8<-- [end:core]

long long brute(long long a, long long b) {
    long long res = 0;
    for (long long x = 0; x <= a; x++) {
        for (long long y = 0; y <= b; y++) {
            if ((x & y) == 0) res++;
        }
    }
    return res;
}

int main() {
    for (long long a = 0; a <= 40; a++) {
        for (long long b = 0; b <= 40; b++) assert(count_pairs(a, b) == brute(a, b));
    }
    long long a, b;
    cin >> a >> b;
    cout << count_pairs(a, b) << '\n';
}
