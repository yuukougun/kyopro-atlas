// 整数の三分探索：x ∈ [0, 10^9] での f(x) = Σ w_i |x − a_i| の最小値を求める。
// f は |x − a_i| の正の数倍の和なので下に凸。平らな部分（最小が続く区間）があってもよい。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), w(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> w[i];
    auto f = [&](long long x) {
        long long s = 0;
        for (int i = 0; i < n; i++) s += w[i] * llabs(x - a[i]);
        return s;
    };

    // --8<-- [start:core]
    long long l = 0, r = 1'000'000'000;  // 最小を与える x は閉区間 [l, r] の中にある
    while (r - l > 2) {                  // 3 点以下になるまで縮める
        long long m1 = l + (r - l) / 3;
        long long m2 = r - (r - l) / 3;  // r − l ≥ 3 なので l < m1 < m2 < r
        if (f(m1) < f(m2)) r = m2;
        else l = m1;
    }
    long long ans = f(l);
    for (long long x = l + 1; x <= r; x++) ans = min(ans, f(x));  // 残りを全部調べる
    cout << ans << '\n';
    // --8<-- [end:core]
}
