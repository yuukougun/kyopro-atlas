#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto& e : a) cin >> e;
    sort(a.begin(), a.end());
    // --8<-- [start:core]
    int lo = lower_bound(a.begin(), a.end(), x) - a.begin();  // x 以上の最初の添字
    int hi = upper_bound(a.begin(), a.end(), x) - a.begin();  // x より大きい最初の添字
    cout << lo << ' ' << hi << ' ' << hi - lo << '\n';        // x の個数は hi - lo
    cout << lo << ' ' << n - lo << '\n';                      // x 未満の個数・x 以上の個数

    auto [first, last] = equal_range(a.begin(), a.end(), x);  // [lo, hi) を一度に
    cout << (last - first) << ' ' << binary_search(a.begin(), a.end(), x) << '\n';
    // --8<-- [end:core]

    // --8<-- [start:set]
    set<int> st(a.begin(), a.end());
    auto p = st.lower_bound(x);  // メンバ関数：O(log N)
    // lower_bound(st.begin(), st.end(), x) と書くと O(N) になる
    cout << (p == st.end() ? -1 : *p) << '\n';
    // --8<-- [end:set]
}
