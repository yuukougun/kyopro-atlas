// 区間の最大部分配列和（空でない部分配列）を、一点更新つきで答える
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「1 p x」（a[p] を x にする）か「2 l r」（[l, r) の最大部分配列和を出力。l < r）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
const long long NEG = -(1LL << 60);  // 「候補がない」を表す十分小さい値

struct S {
    long long sum;   // 区間の和
    long long pre;   // 左端から始まる部分配列の和の最大
    long long suf;   // 右端で終わる部分配列の和の最大
    long long best;  // 区間の中の部分配列の和の最大
};

S e() { return {0, NEG, NEG, NEG}; }  // 空の区間：空でない部分配列がない

S op(S a, S b) {
    return {
        a.sum + b.sum,
        max(a.pre, a.sum + b.pre),                 // a の中で終わるか、a 全体をまたぐ
        max(b.suf, a.suf + b.sum),                 // b の中で始まるか、b 全体をまたぐ
        max({a.best, b.best, a.suf + b.pre}),      // 境目をまたぐ候補を足す
    };
}

S leaf(long long x) { return {x, x, x, x}; }
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
            long long res = seg.prod(l, r).best;
            long long expected = NEG;  // 素朴な O(N^2) で確かめる
            for (int s = l; s < r; s++) {
                long long acc = 0;
                for (int t2 = s; t2 < r; t2++) {
                    acc += a[t2];
                    expected = max(expected, acc);
                }
            }
            assert(res == expected);
            cout << res << '\n';
        }
    }
}
