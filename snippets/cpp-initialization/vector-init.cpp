#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<int> a(n);     // 0 が n 個
    vector<int> b(n, 7);  // 7 が n 個
    vector<int> c{n};     // 値 n が 1 個（大きさ 1）
    vector<int> d{n, 7};  // 値 n と 7 の 2 個
    // --8<-- [end:core]
    cout << a.size() << ' ' << b.size() << ' ' << c.size() << ' ' << d.size() << '\n';
    cout << c[0] << '\n';
    assert(ranges::count(a, 0) == n && ranges::count(b, 7) == n);
}
