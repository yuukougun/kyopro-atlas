// 集合だけを状態にする：相性が 1 の組だけで男女 N 組のペアを作る方法の数（mod 1e9+7）
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// --8<-- [start:core]
long long count_matchings(const vector<vector<int>>& ok) {
    int n = ok.size();
    // dp[S]：男性 0..|S|-1 を、女性の集合 S とちょうどペアにする方法の数
    vector<long long> dp(1 << n, 0);
    dp[0] = 1;                                 // 誰もペアにしない方法は 1 通り
    for (int S = 1; S < (1 << n); S++) {
        int i = __builtin_popcount(S) - 1;     // S の大きさで、次に組む男性が決まる
        for (int j = 0; j < n; j++) {
            if (((S >> j) & 1) && ok[i][j]) {  // 女性 j が S にいて、i と組める
                dp[S] = (dp[S] + dp[S ^ (1 << j)]) % MOD;
            }
        }
    }
    return dp[(1 << n) - 1];
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ok(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> ok[i][j];
    }
    long long ans = count_matchings(ok);
    // 確かめ用：小さい N では女性の並べ方をすべて試す
    if (n <= 8) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long cnt = 0;
        do {
            bool good = true;
            for (int i = 0; i < n; i++) good = good && ok[i][p[i]];
            if (good) cnt++;
        } while (next_permutation(p.begin(), p.end()));
        assert(ans == cnt % MOD);
    }
    cout << ans << '\n';
}
