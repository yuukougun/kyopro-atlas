// 区間加算・区間最小値（ACL の lazy_segtree に標準の型を渡す）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」（[l, r) に x を加える）か「1 l r」（[l, r) の最小値を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;  // INF + 加算の総和が long long に収まる大きさ

long long op(long long a, long long b) { return min(a, b); }
long long e() { return INF; }                                  // min の単位元
long long mapping(long long f, long long x) { return x + f; }  // 値 x に f を加える
long long composition(long long f, long long g) { return f + g; }  // g の後に f
long long id() { return 0; }                                   // 「何もしない」は 0 を加える

// atcoder::lazy_segtree<long long, op, e, long long, mapping, composition, id> seg(a);
// seg.apply(l, r, x);   // [l, r) に x を加える
// seg.prod(l, r);       // [l, r) の最小値（l == r なら INF）
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    atcoder::lazy_segtree<long long, op, e, long long, mapping, composition, id> seg(a);
    vector<long long> naive = a;  // 素朴な方法で答えを確かめる
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long x;
            cin >> x;
            seg.apply(l, r, x);
            for (int j = l; j < r; j++) naive[j] += x;
        } else {
            long long res = seg.prod(l, r);
            long long expected = INF;
            for (int j = l; j < r; j++) expected = min(expected, naive[j]);
            assert(res == expected);
            if (res == INF) cout << "INF" << '\n';  // 空区間
            else cout << res << '\n';
        }
    }
}
