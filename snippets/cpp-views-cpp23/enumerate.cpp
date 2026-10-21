#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // 最大値の位置（同じ値なら最初の位置）を求める
    ptrdiff_t best = -1;
    for (auto [i, x] : a | views::enumerate) {
        static_assert(is_same_v<decltype(i), ptrdiff_t>);  // 添字は ptrdiff_t
        if (best == -1 || x > a[best]) best = i;
    }
    // --8<-- [end:core]
    cout << best << '\n';
}
