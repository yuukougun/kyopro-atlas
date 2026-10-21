// 半分全列挙：n ≤ 40 個の正の整数から好きなだけ選んだ和のうち、t 以下で最大のものを求める。
// 前半と後半の部分和をそれぞれ昇順に列挙し、前半の和 p ごとに後半から t - p 以下の最大を二分探索する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long t;
    cin >> n >> t;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(0 <= n && n <= 40 && t >= 0);
    for (int i = 0; i < n; i++) assert(a[i] >= 1);

    // --8<-- [start:core]
    // v の部分和 2^|v| 個を昇順に返す（空集合の 0 を含む）。
    // 要素を 1 つ足すたびに「今の列」と「今の列 + x」をマージするので、ソートは要らない。
    auto subset_sums = [](const vector<long long>& v) {
        vector<long long> s = {0};
        for (long long x : v) {
            vector<long long> added(s.size()), merged(2 * s.size());
            for (size_t i = 0; i < s.size(); i++) added[i] = s[i] + x;
            merge(s.begin(), s.end(), added.begin(), added.end(), merged.begin());
            s = move(merged);
        }
        return s;
    };

    int h = n / 2;  // 前半 h 個、後半 n - h 個
    vector<long long> left = subset_sums(vector<long long>(a.begin(), a.begin() + h));
    vector<long long> right = subset_sums(vector<long long>(a.begin() + h, a.end()));

    long long best = 0;  // 何も選ばなければ和は 0
    for (long long p : left) {
        if (p > t) continue;
        // right[0] = 0 ≤ t - p なので、t - p 以下の要素は必ずある
        auto it = upper_bound(right.begin(), right.end(), t - p);
        best = max(best, p + *prev(it));
    }
    cout << best << '\n';
    // --8<-- [end:core]
}
