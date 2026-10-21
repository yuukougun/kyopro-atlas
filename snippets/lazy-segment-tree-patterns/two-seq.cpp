// 2 つの列への区間加算と、区間の Σ a_i b_i（mod 998244353）
// 入力：N Q、a_0 … a_{N-1}、b_0 … b_{N-1}、続く Q 行は
//   「0 l r x」（[l, r) の a に x を足す）・「1 l r y」（[l, r) の b に y を足す）・「2 l r」（[l, r) の Σ a_i b_i を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
struct S {
    mint sa, sb, sab;  // Σa・Σb・Σab
    int len;           // 区間の長さ（葉は 1、e() は 0）
};
struct F {
    mint x, y;  // a に x、b に y を足す
};
S op(S p, S q) { return {p.sa + q.sa, p.sb + q.sb, p.sab + q.sab, p.len + q.len}; }
S e() { return {0, 0, 0, 0}; }
S mapping(F f, S s) {
    // Σ(a + x)(b + y) = Σab + yΣa + xΣb + xy・長さ。Σab を先に、更新前の Σa・Σb で作る
    mint sab = s.sab + f.y * s.sa + f.x * s.sb + f.x * f.y * s.len;
    return {s.sa + f.x * s.len, s.sb + f.y * s.len, sab, s.len};
}
F composition(F f, F g) { return {f.x + g.x, f.y + g.y}; }  // 加算どうしは成分ごとの和
F id() { return {0, 0}; }
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    vector<S> init(n);
    for (int i = 0; i < n; i++) init[i] = {a[i], b[i], mint(a[i]) * b[i], 1};
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);
    vector<mint> na(a.begin(), a.end()), nb(b.begin(), b.end());  // 素朴な計算との照合用
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0 || t == 1) {
            long long v;
            cin >> v;
            if (t == 0) seg.apply(l, r, F{v, 0});
            else seg.apply(l, r, F{0, v});
            for (int j = l; j < r; j++) (t == 0 ? na[j] : nb[j]) += v;
        } else {
            mint expected = 0;
            for (int j = l; j < r; j++) expected += na[j] * nb[j];
            S res = seg.prod(l, r);
            assert(res.sab == expected && res.len == r - l);
            cout << res.sab.val() << '\n';
        }
    }
}
