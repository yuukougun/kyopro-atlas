// 長さ K 以上の連続部分列の中央値の最大値を求める。
// 中央値は、偶数個なら小さい方（小さい方から ⌈m/2⌉ 番目）とする。
// 「中央値 ≥ x ⇔ x 以上を +1、未満を −1 にした和が正」と言い換え、x を整数で二分探索する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    assert(1 <= k && k <= n);
    vector<long long> a(n);
    for (auto& v : a) cin >> v;

    // --8<-- [start:core]
    // 可：長さ k 以上の区間で、中央値が x 以上のものがある
    auto check = [&](long long x) {
        vector<int> s(n + 1, 0);  // s[i] = c[0] + … + c[i-1]、c は +1 か −1
        for (int i = 0; i < n; i++) s[i + 1] = s[i] + (a[i] >= x ? 1 : -1);
        int min_left = INT_MAX;  // s[0..r-k] の最小値
        for (int r = k; r <= n; r++) {
            min_left = min(min_left, s[r - k]);
            if (s[r] - min_left > 0) return true;  // 偶数個で小さい方の中央値なので「正」
        }
        return false;
    };
    long long ok = *min_element(a.begin(), a.end());       // 可（中央値は最小値以上）
    long long ng = *max_element(a.begin(), a.end()) + 1;   // 不可（中央値は最大値以下）
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        if (check(mid)) ok = mid;
        else ng = mid;
    }
    cout << ok << '\n';
    // --8<-- [end:core]
}
