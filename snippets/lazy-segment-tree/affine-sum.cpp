// 区間アフィン変換（x → b x + c）・区間和を mod 998244353 で（S に区間の長さを持たせる）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r b c」か「1 l r」（[l, r) の和を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace std;

// --8<-- [start:core]
struct S {
    atcoder::modint998244353 sum;  // 区間の和
    int len;   // 区間の長さ（葉は 1、e() は 0）
};
struct F {
    atcoder::modint998244353 b, c;  // x → b x + c
};
S op(S x, S y) { return {x.sum + y.sum, x.len + y.len}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {f.b * x.sum + f.c * x.len, x.len}; }  // 長さぶん c が増える
F composition(F f, F g) { return {f.b * g.b, f.b * g.c + f.c}; }    // g の後に f
F id() { return {1, 0}; }
// 区間加算は F{1, c}、区間代入は F{0, c} で表せる
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<S> init(n);
    vector<atcoder::modint998244353> naive(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        init[i] = {a, 1};  // 葉の長さは 1
        naive[i] = a;
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            int b, c;
            cin >> b >> c;
            seg.apply(l, r, F{b, c});
            for (int j = l; j < r; j++) naive[j] = naive[j] * b + c;
        } else {
            atcoder::modint998244353 expected = 0;
            for (int j = l; j < r; j++) expected += naive[j];
            S res = seg.prod(l, r);
            assert(res.sum == expected && res.len == r - l);
            cout << res.sum.val() << '\n';
        }
    }
}
