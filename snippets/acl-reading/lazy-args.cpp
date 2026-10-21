#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;
using namespace atcoder;

// --8<-- [start:core]
struct S {
    long long sum;  // 区間の和
    int len;        // 区間の長さ
};
S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }                                       // 長さ 0 の空の区間
using F = long long;                                           // 作用：区間の各要素に f を足す
S mapping(F f, S x) { return {x.sum + f * x.len, x.len}; }     // 作用 f を値 x に施す
F composition(F f, F g) { return f + g; }                      // g を施した後に f を施す
F id() { return 0; }                                           // 何もしない作用（0 を足す）
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    // --8<-- [start:use]
    vector<S> init(n, {0, 1});  // 葉の長さは 1
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);
    // --8<-- [end:use]
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long x;
            cin >> x;
            seg.apply(l, r, x);  // [l, r) に x を足す
        } else {
            cout << seg.prod(l, r).sum << '\n';
        }
    }
}
