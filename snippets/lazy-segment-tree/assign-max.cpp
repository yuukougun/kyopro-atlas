// 区間代入・区間最大値（代入の「なし」を番兵で表す）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」（[l, r) を x にする）か「1 l r」（[l, r) の最大値を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
const long long NONE = LLONG_MAX;  // 代入の「なし」（作用の側）。代入されうる値と重ならない番兵

long long op(long long a, long long b) { return max(a, b); }
long long e() { return LLONG_MIN; }  // max の単位元（値の側。NONE とは別の役割）
long long mapping(long long f, long long x) { return f == NONE ? x : f; }
long long composition(long long f, long long g) { return f == NONE ? g : f; }  // 後の代入 f が勝つ
long long id() { return NONE; }
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    atcoder::lazy_segtree<long long, op, e, long long, mapping, composition, id> seg(a);
    vector<long long> naive = a;
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long x;
            cin >> x;
            seg.apply(l, r, x);
            for (int j = l; j < r; j++) naive[j] = x;
        } else {
            long long res = seg.prod(l, r);
            long long expected = LLONG_MIN;
            for (int j = l; j < r; j++) expected = max(expected, naive[j]);
            assert(res == expected);
            cout << res << '\n';
        }
    }
}
