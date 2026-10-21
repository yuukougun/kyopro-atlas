// 価値を添字にした 0-1 ナップサック：重さの上限 W が大きく、価値の総和 V が小さいとき。
// dp[x] ＝ 価値の和をちょうど x にする重さの最小。答えは dp[x] <= W となる最大の x。
// 小さい N では全探索の答えと突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long W;
    cin >> n >> W;
    vector<long long> w(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    for (int i = 0; i < n; i++) assert(0 <= v[i]);

    // --8<-- [start:core]
    int V = 0;  // 価値の総和（添字の範囲）
    for (int i = 0; i < n; i++) V += v[i];
    const long long INF = LLONG_MAX / 2;  // INF + w が溢れない大きさ
    // dp[x]：ここまでの品物から、価値の和がちょうど x になるように選んだときの重さの最小
    vector<long long> dp(V + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        // 0-1 なので添字（価値）を大きい方から回す
        for (int x = V; x >= v[i]; x--) {
            dp[x] = min(dp[x], dp[x - v[i]] + w[i]);
        }
    }
    int ans = 0;
    for (int x = 0; x <= V; x++) {
        if (dp[x] <= W) ans = x;  // 重さが W 以下で作れる価値の最大
    }
    cout << ans << '\n';
    // --8<-- [end:core]

    if (n <= 15) {  // 全探索で確かめる
        int best = 0;
        for (int s = 0; s < (1 << n); s++) {
            long long sw = 0;
            int sv = 0;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) {
                    sw += w[i];
                    sv += v[i];
                }
            }
            if (sw <= W) best = max(best, sv);
        }
        assert(best == ans);
    }
}
