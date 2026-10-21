// 区間で 2 番目に大きい値とその個数（ACL の segtree に (最大, 個数, 2 番目, 個数) を載せる）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「1 p x」（a[p] を x にする）か「2 l r」（[l, r) で 2 番目に大きい値の個数を出力）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
const long long NONE = LLONG_MIN;  // 「値がない」印。個数 0 と組にして使う

struct S {
    long long v1, c1;  // 最大値とその個数
    long long v2, c2;  // 2 番目に大きい値とその個数（なければ NONE と 0）
};

S e() { return {NONE, 0, NONE, 0}; }  // 空の区間：最大も 2 番目もない

S op(S a, S b) {
    // 4 つの（値, 個数）を大きい順に 2 つだけ残す。同じ値は個数を足す
    S r = e();
    for (auto [v, c] : {pair{a.v1, a.c1}, {a.v2, a.c2}, {b.v1, b.c1}, {b.v2, b.c2}}) {
        if (c == 0) continue;  // 「なし」は飛ばす
        if (v == r.v1) {
            r.c1 += c;
        } else if (v > r.v1) {
            r.v2 = r.v1, r.c2 = r.c1;  // 1 番目が 2 番目に下がる
            r.v1 = v, r.c1 = c;
        } else if (v == r.v2) {
            r.c2 += c;
        } else if (v > r.v2) {
            r.v2 = v, r.c2 = c;
        }
    }
    return r;
}

S leaf(long long x) { return {x, 1, NONE, 0}; }  // 1 要素の区間
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    vector<S> init(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        init[i] = leaf(a[i]);
    }
    atcoder::segtree<S, op, e> seg(init);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int p;
            long long x;
            cin >> p >> x;
            a[p] = x;
            seg.set(p, leaf(x));
        } else {
            int l, r;
            cin >> l >> r;
            S res = seg.prod(l, r);
            // 素朴な方法で確かめる：異なる値を大きい順に並べ、2 番目の値を数える
            set<long long, greater<long long>> vals(a.begin() + l, a.begin() + r);
            long long expected = 0;
            if (vals.size() >= 2) expected = count(a.begin() + l, a.begin() + r, *next(vals.begin()));
            assert(res.c2 == expected);
            cout << res.c2 << '\n';
        }
    }
}
