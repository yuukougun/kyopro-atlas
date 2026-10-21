// 長さ D[i] の区間を、長さ L1・費用 C1・上限 K1 個のセンサー 1 と、長さ L2・費用 C2・上限 K2 個のセンサー 2 で覆う。
// 1 つの区間を複数のセンサーで覆ってよく、はみ出してもよい。費用の最小を求める（覆えなければ -1）。
// 2 種類の個数の両方を添字にせず、センサー 1 の個数を添字、センサー 2 の個数の最小を値にする。
// K1・K2 が小さいときは、両方を添字にした可否の表と突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    long long l1, c1, l2, c2;
    int k1, k2;
    cin >> l1 >> c1 >> k1 >> l2 >> c2 >> k2;

    // --8<-- [start:core]
    const int INF = INT_MAX / 2;
    // dp[j]：ここまでの区間を、センサー 1 をちょうど j 個使って覆うときの、センサー 2 の個数の最小
    vector<int> dp(k1 + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<int> ndp(k1 + 1, INF);
        for (int j = 0; j <= k1; j++) {
            if (dp[j] == INF) continue;
            // この区間でセンサー 1 を a 個使い、残りをセンサー 2 で覆う
            for (int a = 0; j + a <= k1; a++) {
                long long rest = max(0LL, d[i] - l1 * a);
                int b = (rest + l2 - 1) / l2;  // 要るセンサー 2 の個数
                ndp[j + a] = min(ndp[j + a], dp[j] + b);
                if (rest == 0) break;  // これ以上センサー 1 を増やしても得をしない
            }
        }
        dp = move(ndp);
    }
    long long ans = -1;
    for (int j = 0; j <= k1; j++) {
        if (dp[j] > k2) continue;  // センサー 2 の上限を超える
        long long cost = c1 * j + c2 * dp[j];
        if (ans == -1 || cost < ans) ans = cost;
    }
    cout << ans << '\n';
    // --8<-- [end:core]

    if (k1 <= 20 && k2 <= 20) {  // 両方の個数を添字にした可否の表で確かめる
        vector ok(k1 + 1, vector<bool>(k2 + 1, false));
        ok[0][0] = true;
        for (int i = 0; i < n; i++) {
            vector nok(k1 + 1, vector<bool>(k2 + 1, false));
            for (int j = 0; j <= k1; j++) {
                for (int k = 0; k <= k2; k++) {
                    if (!ok[j][k]) continue;
                    for (int a = 0; j + a <= k1; a++) {
                        for (int b = 0; k + b <= k2; b++) {
                            if (l1 * a + l2 * b >= d[i]) nok[j + a][k + b] = true;
                        }
                    }
                }
            }
            ok = nok;
        }
        long long best = -1;
        for (int j = 0; j <= k1; j++) {
            for (int k = 0; k <= k2; k++) {
                if (ok[j][k] && (best == -1 || c1 * j + c2 * k < best)) best = c1 * j + c2 * k;
            }
        }
        assert(best == ans);
    }
}
