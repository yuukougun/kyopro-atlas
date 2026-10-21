// 区間 [l, r) の各位置 i に c + d・i を足す操作と、区間和
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r c d」か「1 l r」（[l, r) の和を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
struct S {
    long long sum;   // 区間の和
    long long len;   // 区間の長さ
    long long isum;  // 区間の添字の和 Σi（葉 i は i）
};
struct F {
    long long c, d;  // 位置 i に c + d・i を足す（i は列全体での添字）
};
S op(S x, S y) { return {x.sum + y.sum, x.len + y.len, x.isum + y.isum}; }
S e() { return {0, 0, 0}; }
S mapping(F f, S x) { return {x.sum + f.c * x.len + f.d * x.isum, x.len, x.isum}; }
F composition(F f, F g) { return {f.c + g.c, f.d + g.d}; }  // 1 次式どうしの和
F id() { return {0, 0}; }
// 「l から始めて初項 a・公差 d」を足すなら、c = a − d・l にして F{c, d} を作用させる
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> naive(n);
    vector<S> init(n);
    for (int i = 0; i < n; i++) {
        cin >> naive[i];
        init[i] = {naive[i], 1, i};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long c, d;
            cin >> c >> d;
            seg.apply(l, r, F{c, d});
            for (int j = l; j < r; j++) naive[j] += c + d * j;
        } else {
            long long expected = 0;
            for (int j = l; j < r; j++) expected += naive[j];
            long long res = seg.prod(l, r).sum;
            assert(res == expected);
            cout << res << '\n';
        }
    }
}
