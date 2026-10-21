// L <= x <= y <= R で、x AND y = 0 となる組 (x, y) の個数
// 入力：L R（0 <= L <= R <= 10^11。答えが long long に収まる範囲）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_pairs(long long l, long long r) {
    // dp[gl][lr][eq]：上の bit から決めた途中の (x, y) のうち、
    //   gl = 1 なら x が L と一致（下限に張り付いている）、
    //   lr = 1 なら y が R と一致（上限に張り付いている）、
    //   eq = 1 なら x と y が一致しているものの個数
    // x <= R と L <= y は L <= x <= y <= R から従うので、フラグを持たない
    long long dp[2][2][2] = {};
    dp[1][1][1] = 1;
    for (int k = 40; k >= 0; k--) {  // 10^11 < 2^37
        int bl = (l >> k) & 1, br = (r >> k) & 1;
        long long nd[2][2][2] = {};
        for (int gl = 0; gl < 2; gl++) {
            for (int lr = 0; lr < 2; lr++) {
                for (int eq = 0; eq < 2; eq++) {
                    long long cur = dp[gl][lr][eq];
                    if (cur == 0) continue;
                    for (int bx = 0; bx < 2; bx++) {
                        for (int by = 0; by < 2; by++) {
                            if (bx & by) continue;
                            if (gl && bx < bl) continue;  // x が L を下回る
                            if (lr && by > br) continue;  // y が R を上回る
                            if (eq && bx > by) continue;  // x が y を上回る
                            int ngl = (gl && bx == bl) ? 1 : 0;
                            int nlr = (lr && by == br) ? 1 : 0;
                            int neq = (eq && bx == by) ? 1 : 0;
                            nd[ngl][nlr][neq] += cur;
                        }
                    }
                }
            }
        }
        memcpy(dp, nd, sizeof(dp));
    }
    long long res = 0;
    for (int gl = 0; gl < 2; gl++) {
        for (int lr = 0; lr < 2; lr++) {
            for (int eq = 0; eq < 2; eq++) res += dp[gl][lr][eq];
        }
    }
    return res;
}
// --8<-- [end:core]

long long brute(long long l, long long r) {
    long long res = 0;
    for (long long x = l; x <= r; x++) {
        for (long long y = x; y <= r; y++) {
            if ((x & y) == 0) res++;
        }
    }
    return res;
}

int main() {
    for (long long l = 0; l <= 40; l++) {
        for (long long r = l; r <= 40; r++) assert(count_pairs(l, r) == brute(l, r));
    }
    long long l, r;
    cin >> l >> r;
    cout << count_pairs(l, r) << '\n';
}
