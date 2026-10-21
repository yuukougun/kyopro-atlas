// 0-1 ナップサック：重さ w[i]・価値 v[i] の品物を各 1 個まで選び、重さの合計 W 以下での価値の和の最大を求める。
// 1 次元の配列を使い回し、重さを大きい方から更新する。小さい N では全探索の答えと突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    vector<int> w(n);
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    for (int i = 0; i < n; i++) assert(1 <= w[i]);

    // --8<-- [start:core]
    // dp[j]：ここまでの品物から重さの合計 j 以下で選んだときの価値の最大（何も選ばなければ 0）
    vector<long long> dp(W + 1, 0);
    for (int i = 0; i < n; i++) {
        // 大きい方から：dp[j - w[i]] はまだ品物 i を見る前の値なので、品物 i は 1 回しか入らない
        for (int j = W; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[W] << '\n';
    // --8<-- [end:core]

    if (n <= 15) {  // 全探索で確かめる
        long long best = 0;
        for (int s = 0; s < (1 << n); s++) {
            long long sw = 0, sv = 0;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) {
                    sw += w[i];
                    sv += v[i];
                }
            }
            if (sw <= W) best = max(best, sv);
        }
        assert(best == dp[W]);
    }
}
