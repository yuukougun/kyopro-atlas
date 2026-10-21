#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // 広義単調増加の区間に分けて、いちばん長い区間の長さを求める
    ptrdiff_t best = 0;
    for (auto r : a | views::chunk_by(less_equal{})) best = max(best, ranges::distance(r));
    // --8<-- [end:core]
    cout << best << '\n';
}
