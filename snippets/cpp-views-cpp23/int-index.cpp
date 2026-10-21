#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:core]
    int best = -1;  // 3 以上の値がある最後の位置
    for (auto [i, x] : views::zip(views::iota(0), v)) {
        static_assert(is_same_v<decltype(i), int>);  // 始まりの 0 が int なので i も int
        if (x >= 3) best = max(best, i);
    }
    // --8<-- [end:core]
    cout << best << '\n';
}
