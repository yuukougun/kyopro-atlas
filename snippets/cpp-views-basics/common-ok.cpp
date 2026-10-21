#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    auto r = a | views::take_while([](int x) { return x > 0; }) | views::common;
    vector<int> b(r.begin(), r.end());  // begin と end の型がそろったので通る
    // --8<-- [end:core]
    static_assert(ranges::common_range<decltype(r)>);
    cout << b.size() << '\n';
}
