#include <bits/stdc++.h>
using namespace std;

// S_0 は空文字列、S_n = S_{n-1} + c_n + S_{n-1}（c_n = 'a' + (n - 1) mod 26）。
// |S_n| = 2^n - 1。N <= 10^18、1 <= K <= min(|S_N|, 10^18) のとき、S_N の K 文字目を求める。

// --8<-- [start:core]
long long len[61];  // len[n] = |S_n| = 2^n - 1（n <= 60 なら long long に収まる）

// S_n の k 文字目（1-indexed）
char rec(int n, long long k) {
    long long half = len[n - 1];
    if (k <= half) return rec(n - 1, k);          // 前の S_{n-1}
    if (k == half + 1) return 'a' + (n - 1) % 26; // 真ん中の c_n
    return rec(n - 1, k - half - 1);              // 後ろの S_{n-1}
}

char solve(long long n, long long k) {
    // S_n は S_{n-1} で始まるので、S_N の先頭 len[m] 文字は S_m と同じ。
    // K <= 10^18 < len[60] なので、レベルを 60 に下げても K 文字目は変わらない
    int m = (int)min(n, 60LL);
    return rec(m, k);
}
// --8<-- [end:core]

int main() {
    len[0] = 0;
    for (int i = 1; i <= 60; i++) len[i] = 2 * len[i - 1] + 1;
    // 答えは c_{(K の末尾に並ぶ 0 の個数) + 1} になるはず
    for (long long k = 1; k <= 100000; k++) {
        assert(solve(1000000000000000000LL, k) == 'a' + __builtin_ctzll(k) % 26);
    }
    long long n, k;
    cin >> n >> k;
    cout << solve(n, k) << '\n';
}
