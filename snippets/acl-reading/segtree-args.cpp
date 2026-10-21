#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

// --8<-- [start:core]
int op(int a, int b) { return min(a, b); }  // 結合的な演算：区間の最小値
int e() { return INT_MAX; }                 // 単位元：min(x, INT_MAX) = x
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:use]
    segtree<int, op, e> seg(a);  // S = int、op と e は関数の名前
    // seg.prod(l, r) は [l, r) の最小値。空区間なら e()
    // --8<-- [end:use]
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << seg.prod(l, r) << '\n';
    }
}
