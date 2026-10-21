#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 半開区間 [l, r) と重み w の列から、互いに重ならない区間の重みの和の最大を返す
long long max_weight(vector<array<long long, 3>> iv) {
    int n = iv.size();
    sort(iv.begin(), iv.end(), [](const auto& a, const auto& b) { return a[1] < b[1]; });
    vector<long long> rs(n);
    for (int i = 0; i < n; i++) rs[i] = iv[i][1];
    // dp[i] ＝ 右端の小さい方から i 個の区間だけを使うときの、重みの和の最大
    vector<long long> dp(n + 1, 0);
    for (int i = 0; i < n; i++) {
        auto [l, r, w] = iv[i];
        // 右端が l 以下の区間は、区間 i と一緒に選べる。その個数 j を二分探索で求める
        int j = upper_bound(rs.begin(), rs.begin() + i, l) - rs.begin();
        dp[i + 1] = max(dp[i], dp[j] + w);  // 区間 i を選ばない／選ぶ
    }
    return dp[n];
}
// --8<-- [end:core]

int main() {
    assert(max_weight({}) == 0);
    assert(max_weight({{0, 10, 5}, {1, 2, 1}, {3, 4, 1}}) == 5);  // 個数の最大とは違う区間を選ぶ
    int n;
    cin >> n;
    vector<array<long long, 3>> iv(n);
    for (auto& [l, r, w] : iv) cin >> l >> r >> w;
    cout << max_weight(iv) << '\n';
}
