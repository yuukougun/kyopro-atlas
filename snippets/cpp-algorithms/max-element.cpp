#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // n >= 1
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    auto it = max_element(a.begin(), a.end());  // 値ではなくイテレータ（最大が複数なら最初）
    cout << *it << ' ' << (it - a.begin()) << '\n';  // 値と添字

    int x = 7, y = 2, z = 5;
    cout << max({x, y, z}) << ' ' << clamp(x, 0, 5) << '\n';  // 3 つ以上の最大、[0, 5] に収める

    long long c = count(a.begin(), a.end(), a[0]);  // 戻り値は ptrdiff_t（int ではない）
    cout << c << '\n';
    // --8<-- [end:core]
}
