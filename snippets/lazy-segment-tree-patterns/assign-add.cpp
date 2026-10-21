// 区間代入と区間加算の両方と、区間和・区間最小値
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」（[l, r) を x にする）・「1 l r x」（[l, r) に x を足す）・「2 l r」（和と最小値を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;
struct S {
    long long sum, mn;
    long long len;
};
struct F {
    bool set;      // 代入するか（「なし」を値と別のフラグで持つ）
    long long v;   // 代入する値（set のときだけ意味がある）
    long long add; // 代入の後に足す値
};  // 作用は x → (set ? v : x) + add
S op(S x, S y) { return {x.sum + y.sum, min(x.mn, y.mn), x.len + y.len}; }
S e() { return {0, INF, 0}; }
S mapping(F f, S x) {
    if (x.len == 0) return x;  // 単位元はそのまま
    if (f.set) return {(f.v + f.add) * x.len, f.v + f.add, x.len};
    return {x.sum + f.add * x.len, x.mn + f.add, x.len};
}
F composition(F f, F g) {  // g の後に f
    if (f.set) return f;                // 後の代入が前をすべて消す
    return {g.set, g.v, g.add + f.add};  // 加算だけなら g に足し込む
}
F id() { return {false, 0, 0}; }
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> naive(n);
    vector<S> init(n);
    for (int i = 0; i < n; i++) {
        cin >> naive[i];
        init[i] = {naive[i], naive[i], 1};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0 || t == 1) {
            long long x;
            cin >> x;
            if (t == 0) seg.apply(l, r, F{true, x, 0});
            else seg.apply(l, r, F{false, 0, x});
            for (int j = l; j < r; j++) naive[j] = (t == 0 ? x : naive[j] + x);
        } else {
            long long es = 0, em = INF;
            for (int j = l; j < r; j++) es += naive[j], em = min(em, naive[j]);
            S res = seg.prod(l, r);
            assert(res.sum == es && res.mn == em);
            cout << res.sum << ' ' << (res.mn == INF ? string("INF") : to_string(res.mn)) << '\n';
        }
    }
}
