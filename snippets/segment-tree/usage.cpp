// 一点更新・区間最小値（ACL の segtree）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 p x」（a[p] を x にする）か「1 l r」（[l, r) の最小値を出力）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;  // どの要素よりも大きい値を単位元にする

long long op(long long a, long long b) { return min(a, b); }
long long e() { return INF; }  // min(x, INF) = x

// atcoder::segtree<long long, op, e> seg(a);  // a は vector<long long>。seg(n) なら全要素が e()
// seg.set(p, x);      // a[p] を x にする
// seg.get(p);         // a[p]
// seg.prod(l, r);     // [l, r) の最小値（l == r なら e()）
// seg.all_prod();     // 全体の最小値
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    atcoder::segtree<long long, op, e> seg(a);
    vector<long long> naive = a;  // 素朴な方法で答えを確かめる
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long x;
            cin >> p >> x;
            seg.set(p, x);
            naive[p] = x;
            assert(seg.get(p) == x);
        } else {
            int l, r;
            cin >> l >> r;
            long long res = seg.prod(l, r);
            long long expected = INF;
            for (int j = l; j < r; j++) expected = min(expected, naive[j]);
            assert(res == expected);
            if (res == INF) cout << "INF" << '\n';  // 空区間
            else cout << res << '\n';
        }
    }
    if (n > 0) assert(seg.all_prod() == *min_element(naive.begin(), naive.end()));
}
