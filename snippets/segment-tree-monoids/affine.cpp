// 一次関数の列の一点の差し替えと、区間の合成を x に施した値（mod 998244353）
// 入力：N Q、続く N 行に c_i d_i（f_i(x) = c_i x + d_i）、
//       続く Q 行は「1 p c d」（f_p を差し替える）か「2 l r x」（f_{r-1}(…f_l(x)…) を出力）
#include <bits/stdc++.h>
#include <atcoder/modint>
#include <atcoder/segtree>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
struct S {
    mint c, d;  // x → c x + d
};

S e() { return {1, 0}; }  // 恒等写像 x → x

// a を施してから b を施す：b(a(x)) = b.c (a.c x + a.d) + b.d
S op(S a, S b) { return {a.c * b.c, b.c * a.d + b.d}; }

// seg.prod(l, r) は f_l を最初に、f_{r-1} を最後に施す合成になる
// mint y = res.c * x + res.d;
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<S> f(n);
    for (int i = 0; i < n; i++) {
        int c, d;
        cin >> c >> d;
        f[i] = {c, d};
    }
    atcoder::segtree<S, op, e> seg(f);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, c, d;
            cin >> p >> c >> d;
            f[p] = {c, d};
            seg.set(p, f[p]);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            S res = seg.prod(l, r);
            mint y = res.c * x + res.d;
            mint expected = x;  // 素朴に左から順に施して確かめる
            for (int j = l; j < r; j++) expected = f[j].c * expected + f[j].d;
            assert(y == expected);
            cout << y.val() << '\n';
        }
    }
}
