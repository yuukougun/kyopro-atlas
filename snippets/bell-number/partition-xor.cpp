#include <bits/stdc++.h>
using namespace std;

// N 個の値を組に分けるすべての分け方について「組ごとの和の XOR」を求め、
// 異なる値の個数を返す（N <= 12 なら分け方は B_12 = 4213597 通り）
int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // --8<-- [start:core]
    vector<long long> sum;     // 今ある組ごとの和
    vector<long long> found;   // 葉で得た XOR（後でソートして数える）
    found.reserve(4213597);   // N <= 12 なら葉は B_12 = 4213597 個以下
    auto dfs = [&](auto&& self, int i, long long x) -> void {
        // x は今ある組の和の XOR（差分で更新するので葉では O(1)）
        if (i == n) {
            found.push_back(x);
            return;
        }
        for (int g = 0; g < (int)sum.size(); g++) {  // 既存の組 g に入れる
            long long before = sum[g];
            sum[g] += a[i];
            self(self, i + 1, x ^ before ^ sum[g]);
            sum[g] = before;
        }
        sum.push_back(a[i]);  // 新しい組を作る（番号は今の組の数の 1 通り）
        self(self, i + 1, x ^ a[i]);
        sum.pop_back();
    };
    dfs(dfs, 0, 0);
    ranges::sort(found);
    long long kinds = unique(found.begin(), found.end()) - found.begin();
    // --8<-- [end:core]

    cout << kinds << '\n';
}
