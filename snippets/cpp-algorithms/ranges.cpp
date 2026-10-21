#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // n >= 1
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:core]
    ranges::sort(v);              // sort(v.begin(), v.end()) と同じ
    ranges::sort(v, greater{});   // 降順
    auto [mn, mx] = ranges::minmax(v);  // 値の組（イテレータではない）
    cout << mn << ' ' << mx << ' ' << ranges::max(v) << '\n';
    cout << ranges::count(v, v[0]) << ' '
         << ranges::any_of(v, [](int x) { return x < 0; }) << '\n';
    // --8<-- [end:core]
    for (int x : v) cout << x << ' ';
    cout << '\n';
}
