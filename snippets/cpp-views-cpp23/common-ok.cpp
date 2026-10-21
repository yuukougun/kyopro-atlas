#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // g++-13 での代わり：common で begin と end の型をそろえてから、イテレータの組で作る
    auto z = views::zip(a, views::iota(0)) | views::common;
    vector<pair<int, int>> p(z.begin(), z.end());
    // --8<-- [end:core]
    ranges::sort(p);
    for (auto [x, i] : p) cout << i << ' ';
    cout << '\n';
}
