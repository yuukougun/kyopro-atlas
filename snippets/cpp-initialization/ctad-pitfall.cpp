#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:core]
    vector w{v.begin(), v.end()};   // vector<vector<int>::iterator>。イテレータ 2 個
    vector u(v.begin(), v.end());   // vector<int>。v の要素のコピー
    vector c{v};                    // vector<int>。v のコピー（vector<vector<int>> ではない）
    static_assert(is_same_v<decltype(w), vector<vector<int>::iterator>>);
    static_assert(is_same_v<decltype(u), vector<int>>);
    static_assert(is_same_v<decltype(c), vector<int>>);
    // --8<-- [end:core]
    cout << w.size() << ' ' << u.size() << ' ' << c.size() << '\n';
}
