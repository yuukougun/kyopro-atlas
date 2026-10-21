#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // 「ここでは a が昇順のはず」という自分の思い込みを書いておく
    assert(is_sorted(a.begin(), a.end()));
    int lo = 0, hi = n;  // a[lo, hi) で 10 以上の最初の位置を探す
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] >= 10) hi = mid;
        else lo = mid + 1;
    }
    assert(0 <= lo && lo <= n);  // 外れたら Assertion ... failed と出て RE になる
    // --8<-- [end:core]
    cout << lo << '\n';
}
