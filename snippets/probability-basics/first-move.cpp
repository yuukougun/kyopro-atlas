// 全確率の公式：最初の出目 v（1〜N が各 1/N）で場合分けし、
// 「v から始めて、裏が出る前に K 以上へ届く確率」を足す。
// 届く確率は、必要な表の回数を t として (1/2)^t（1 回でも裏なら 0 になって負け）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    assert(1 <= n && 1 <= k);

    // --8<-- [start:core]
    double ans = 0.0;
    for (int v = 1; v <= n; v++) {
        double p = 1.0;          // P(v から始めて K 以上に届く)
        long long x = v;
        while (x < k) {          // 表が出るたびに 2 倍。届くまで確率を半分にする
            x *= 2;
            p /= 2;
        }
        ans += p / n;            // P(最初が v) × P(届く | 最初が v)
    }
    cout << fixed << setprecision(12) << ans << '\n';  // 既定の 6 桁では誤差の条件を満たさないことがある
    // --8<-- [end:core]
}
