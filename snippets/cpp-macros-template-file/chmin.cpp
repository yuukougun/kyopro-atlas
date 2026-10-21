#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T, class U>
bool chmin(T& a, const U& b) {
    return b < a ? (a = b, true) : false;  // 小さくなったら書き換えて true
}
template <class T, class U>
bool chmax(T& a, const U& b) {
    return a < b && (a = b, true);  // a < b が偽なら右は評価されず false
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:use]
    long long mn = 1LL << 60, mx = 0;
    int updates = 0;
    for (long long x : a) {
        if (chmin(mn, x)) updates++;  // 最小値が更新された回数を数える
        chmax(mx, 0);                 // long long と int の組でも通る
        chmax(mx, x);
    }
    // --8<-- [end:use]
    cout << mn << ' ' << mx << ' ' << updates << '\n';
}
