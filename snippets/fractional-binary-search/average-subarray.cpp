// 長さ K 以上の連続部分列の平均の最大値を求める。
// 「平均 ≥ x ⇔ 各要素から x を引いた和 ≥ 0」と言い換え、x を実数の二分探索で求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    assert(1 <= k && k <= n);
    vector<double> a(n);
    for (auto& v : a) cin >> v;

    // --8<-- [start:core]
    // 可：長さ k 以上の区間で、平均が x 以上のものがある
    auto check = [&](double x) {
        vector<double> s(n + 1, 0.0);  // s[i] = (a[0] - x) + … + (a[i-1] - x)
        for (int i = 0; i < n; i++) s[i + 1] = s[i] + (a[i] - x);
        double min_left = 1e18;  // s[0..r-k] の最小値
        for (int r = k; r <= n; r++) {
            min_left = min(min_left, s[r - k]);
            if (s[r] - min_left >= 0) return true;  // 区間 [l, r) の和 ≥ 0
        }
        return false;
    };
    double lo = *min_element(a.begin(), a.end());        // 可（平均は最小値以上）
    double hi = *max_element(a.begin(), a.end()) + 1.0;  // 不可（平均は最大値以下）
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    cout << fixed << setprecision(9) << lo << '\n';
    // --8<-- [end:core]
}
