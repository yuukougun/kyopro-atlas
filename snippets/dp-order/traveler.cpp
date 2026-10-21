#include <bits/stdc++.h>
using namespace std;

// 数直線上のボール（座標 x、色 c は 1..n）を色の小さい順に全部回収し、原点に戻る最短距離。
// --8<-- [start:core]
long long min_travel(const vector<long long>& x, const vector<int>& c, int n) {
    const long long INF = LLONG_MAX / 4;
    vector<long long> lo(n + 1, INF), hi(n + 1, -INF);
    for (int i = 0; i < (int)x.size(); i++) {
        lo[c[i]] = min(lo[c[i]], x[i]);
        hi[c[i]] = max(hi[c[i]], x[i]);
    }
    // 色 k まで回収し終えて、左端（pos[0]）か右端（pos[1]）にいるときの最短距離
    long long pos[2] = {0, 0}, dp[2] = {0, 0};
    for (int k = 1; k <= n; k++) {          // 色の小さい順：前の色が確定している
        if (lo[k] == INF) continue;         // その色のボールがない
        long long w = hi[k] - lo[k], ndp[2] = {INF, INF};
        for (int s = 0; s < 2; s++) {
            ndp[0] = min(ndp[0], dp[s] + abs(pos[s] - hi[k]) + w);  // 右端→左端で終わる
            ndp[1] = min(ndp[1], dp[s] + abs(pos[s] - lo[k]) + w);  // 左端→右端で終わる
        }
        pos[0] = lo[k], pos[1] = hi[k];
        dp[0] = ndp[0], dp[1] = ndp[1];
    }
    return min(dp[0] + abs(pos[0]), dp[1] + abs(pos[1]));
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> x(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> c[i];
    cout << min_travel(x, c, n) << '\n';
}
