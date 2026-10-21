// 半分全列挙（個数ごと）：n ≤ 40 個の正の整数からちょうど k 個を選び、和が p 以下になる選び方の数を求める。
// 前半・後半の部分和を「選んだ個数」ごとの列に分けて持ち、前半 c 個と後半 k - c 個を組み合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    long long p;
    cin >> n >> k >> p;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(1 <= n && n <= 40 && 0 <= k && k <= n && p >= 0);
    for (int i = 0; i < n; i++) assert(a[i] >= 1);

    // --8<-- [start:core]
    // sums[c] ＝ v から c 個を選んだときの和の一覧（昇順）
    auto by_count = [](const vector<long long>& v) {
        int m = v.size();
        vector<vector<long long>> sums(m + 1);
        for (int mask = 0; mask < (1 << m); mask++) {  // m ≤ 20 なので int でよい
            long long s = 0;
            for (int i = 0; i < m; i++) {
                if (mask >> i & 1) s += v[i];
            }
            sums[popcount((unsigned)mask)].push_back(s);
        }
        for (auto& row : sums) sort(row.begin(), row.end());
        return sums;
    };

    int h = n / 2;
    auto left = by_count(vector<long long>(a.begin(), a.begin() + h));
    auto right = by_count(vector<long long>(a.begin() + h, a.end()));

    long long ans = 0;  // 最大で C(40, 20) ≈ 1.4×10^11 なので long long
    for (int c = 0; c <= k; c++) {
        int d = k - c;  // 後半から選ぶ個数
        if (c > h || d > n - h) continue;
        const auto& r = right[d];
        for (long long s : left[c]) {
            if (s > p) break;  // left[c] は昇順なので、この先も超える
            ans += upper_bound(r.begin(), r.end(), p - s) - r.begin();  // p - s 以下の個数
        }
    }
    cout << ans << '\n';
    // --8<-- [end:core]
}
