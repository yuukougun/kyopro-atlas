// 個数制限付きナップサック：重さ w[i]・価値 v[i] の品物が b[i] 個ずつあるとき、重さの合計 W 以下での価値の和の最大。
// 個数を 1, 2, 4, …, 残り のまとまりに分け（二進分解）、まとまりを 1 つの品物とみて 0-1 ナップサックを解く。
// 使う個数を全部試す素朴な DP と突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    vector<int> w(n), b(n);
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i] >> b[i];
    for (int i = 0; i < n; i++) assert(1 <= w[i] && 0 <= b[i]);

    // --8<-- [start:core]
    vector<long long> dp(W + 1, 0);
    for (int i = 0; i < n; i++) {
        int rest = b[i];
        for (int k = 1; rest > 0; k *= 2) {
            int c = min(k, rest);  // 1, 2, 4, … と取り、最後は残りをまとめる
            rest -= c;
            long long cw = (long long)c * w[i];
            long long cv = c * v[i];
            for (long long j = W; j >= cw; j--) {  // まとまりを 1 つの品物とみた 0-1 の更新
                dp[j] = max(dp[j], dp[j - cw] + cv);
            }
        }
    }
    cout << dp[W] << '\n';
    // --8<-- [end:core]

    // 素朴な方法：品物 i を k 個（0 ≤ k ≤ b[i]）使う場合を全部試す
    vector<long long> naive(W + 1, 0);
    for (int i = 0; i < n; i++) {
        vector<long long> next = naive;
        for (int j = 0; j <= W; j++) {
            for (long long k = 1; k <= b[i] && k * w[i] <= j; k++) {
                next[j] = max(next[j], naive[j - k * w[i]] + k * v[i]);
            }
        }
        naive = next;
    }
    assert(naive[W] == dp[W]);
}
