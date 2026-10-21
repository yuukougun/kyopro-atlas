// 最小値の最大化：長さ len の棒を、候補の位置 a[0] < … < a[n-1] から k か所選んで切り、
// 最も短いピースの長さを最大にする。答え x を二分探索し、判定は左から貪欲に切る。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    long long len;
    cin >> n >> len >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(1 <= k && k <= n);
    for (int i = 0; i < n; i++) assert(0 < a[i] && a[i] < len && (i == 0 || a[i - 1] < a[i]));

    // --8<-- [start:core]
    // 判定：どのピースも長さ x 以上にして、k + 1 個以上に分けられるか（x について単調）
    auto check = [&](long long x) -> bool {
        int pieces = 0;
        long long prev = 0;  // 直前に切った位置
        for (int i = 0; i < n; i++) {
            if (a[i] - prev >= x) {  // 長さ x 以上になった最初の位置で切る
                pieces++;
                prev = a[i];
            }
        }
        if (len - prev >= x) pieces++;  // 右端の残り（足りなければ直前のピースに合わせる）
        return pieces >= k + 1;
    };

    long long ok = 0;        // x = 0 は必ず可（番兵）
    long long ng = len + 1;  // 棒より長いピースは作れないので不可（番兵）
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        if (check(mid)) ok = mid;
        else ng = mid;
    }
    cout << ok << '\n';  // 可の側の端が答え
    // --8<-- [end:core]
}
