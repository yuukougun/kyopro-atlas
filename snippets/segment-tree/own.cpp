// セグメント木を自作する（非再帰。ACL と同じ配置）
// 例として、可換でない演算（1 次関数の合成）を載せ、素朴な計算と照らし合わせる
// 入力：N Q、続く N 行に c_i d_i（f_i(x) = c_i x + d_i）、
//       続く Q 行は「0 p c d」（f_p を差し替える）か「1 l r x」（f_{r-1}(…f_l(x)…) mod 998244353 を出力）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size;
    vector<S> d;  // d[k]：ノード k が受け持つ区間の総積。葉 i は d[size + i]
    SegTree(const vector<S>& a) : n(a.size()), size(1) {
        while (size < n) size *= 2;
        d.assign(2 * size, e());  // 余りの葉は単位元
        for (int i = 0; i < n; i++) d[size + i] = a[i];
        for (int k = size - 1; k >= 1; k--) d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    void set(int p, S x) {  // 葉を書き換え、根まで作り直す
        p += size;
        d[p] = x;
        for (p /= 2; p >= 1; p /= 2) d[p] = op(d[2 * p], d[2 * p + 1]);
    }
    S get(int p) const { return d[size + p]; }
    S prod(int l, int r) const {  // [l, r) の総積。l == r なら e()
        S sml = e(), smr = e();  // 左端から集めた積・右端から集めた積
        for (l += size, r += size; l < r; l /= 2, r /= 2) {
            if (l & 1) sml = op(sml, d[l++]);  // l が右の子なら使って右隣へ
            if (r & 1) smr = op(d[--r], smr);  // r - 1 が左の子なら使って左隣へ
        }
        return op(sml, smr);  // 左の積を先に置く
    }
};
// --8<-- [end:core]

const long long MOD = 998244353;
struct F { long long c, d; };  // x ↦ c x + d
F op(F f, F g) { return {f.c * g.c % MOD, (f.d * g.c + g.d) % MOD}; }  // f を施してから g
F e() { return {1, 0}; }  // 恒等写像

int main() {
    int n, q;
    cin >> n >> q;
    vector<F> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].c >> a[i].d;
    SegTree<F, op, e> seg(a);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long c, d;
            cin >> p >> c >> d;
            seg.set(p, {c, d});
            a[p] = {c, d};
            assert(seg.get(p).c == c && seg.get(p).d == d);
        } else {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            F f = seg.prod(l, r);
            long long res = (f.c * x + f.d) % MOD;
            long long expected = x;  // 素朴に左から順に施す
            for (int j = l; j < r; j++) expected = (a[j].c * expected + a[j].d) % MOD;
            assert(res == expected);
            cout << res << '\n';
        }
    }
}
