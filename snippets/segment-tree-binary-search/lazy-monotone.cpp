// 広義単調増加な列で「値が [L, R] に入る要素すべてに +1」を、遅延セグメント木上の二分探索で行う
// 入力：N Q、B_0 ≤ … ≤ B_{N-1}、続く Q 行は「L R」。最後に列を出力する
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

long long op(long long a, long long b) { return max(a, b); }
long long e() { return LLONG_MIN; }
long long mapping(long long f, long long x) { return x + f; }
long long composition(long long f, long long g) { return f + g; }
long long id() { return 0; }

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    atcoder::lazy_segtree<long long, op, e, long long, mapping, composition, id> seg(b);
    vector<long long> naive = b;
    for (int t = 0; t < q; t++) {
        long long L, R;
        cin >> L >> R;
        // --8<-- [start:core]
        // 列は広義単調増加なので、値が L 以上の要素は後ろにまとまっている
        int i = seg.max_right(0, [&](long long v) { return v < L; });   // 初めて L 以上になる位置
        int j = seg.max_right(0, [&](long long v) { return v <= R; });  // 初めて R を超える位置
        seg.apply(i, j, 1);  // [i, j) が値 [L, R] の要素。+1 しても値は R + 1 以下で、単調さは崩れない
        // --8<-- [end:core]
        for (auto& v : naive) if (L <= v && v <= R) v++;
    }
    for (int i = 0; i < n; i++) {
        assert(seg.get(i) == naive[i]);
        cout << seg.get(i) << (i + 1 < n ? ' ' : '\n');
    }
}
