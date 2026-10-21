#include <bits/stdc++.h>
using namespace std;

// 正の整数の集合に「異なる 2 つの値を選び、差を書き足す」操作を何度でも行うとき、
// 作れる値を全探索で求め、「全体の gcd の倍数で、最大値以下の正の数」という予想と
// 一致するかを assert で確かめる（予想の必要性と十分性を小さい値で確かめる実験）。
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    set<int> s(a.begin(), a.end());
    bool changed = true;
    while (changed) {  // 新しい値が出なくなるまで差を書き足す
        changed = false;
        vector<int> v(s.begin(), s.end());
        for (int x : v) {
            for (int y : v) {
                if (x > y && !s.count(x - y)) {
                    s.insert(x - y);
                    changed = true;
                }
            }
        }
    }
    int g = 0, mx = 0;
    for (int x : a) {
        g = gcd(g, x);
        mx = max(mx, x);
    }
    // 予想：作れる値の集合 ＝ {g, 2g, …, mx}
    set<int> expected;
    for (int x = g; x <= mx; x += g) expected.insert(x);
    assert(s == expected);
    // --8<-- [end:core]
    bool first = true;
    for (int x : s) {
        cout << (first ? "" : " ") << x;
        first = false;
    }
    cout << '\n';
    return 0;
}
