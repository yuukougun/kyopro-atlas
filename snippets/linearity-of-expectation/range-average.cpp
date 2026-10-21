// 区間 [l, r) の値をすべて集め、区間内の一様に選んだ位置に置く操作を順に行う。
// 各位置の値の期待値は「区間の各位置を区間の平均で上書きする」操作で追える。
// 入力：N M、A_1..A_N、続く M 行に L R（1-indexed の閉区間）。出力：各位置の期待値 mod 998244353
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

struct S {
    mint sum;
    int len;
};
S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }

struct F {
    bool has;  // 上書きがあるか
    mint v;    // 上書きする値
};
S mapping(F f, S s) { return f.has ? S{f.v * s.len, s.len} : s; }
F composition(F f, F g) { return f.has ? f : g; }  // 後から来た f を優先
F id() { return {false, 0}; }

int main() {
    int n, m;
    cin >> n >> m;
    vector<S> init(n);
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        init[i] = {mint(a), 1};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(init);
    for (int k = 0; k < m; k++) {
        int l, r;
        cin >> l >> r;
        l--;  // 閉区間 [L, R]（1-indexed）を半開区間 [l, r)（0-indexed）に直す
        // --8<-- [start:core]
        // 期待値の配列のまま、区間を区間の平均で上書きする
        mint avg = seg.prod(l, r).sum / (r - l);
        seg.apply(l, r, F{true, avg});
        // --8<-- [end:core]
    }
    for (int i = 0; i < n; i++) {
        cout << seg.get(i).sum.val() << (i + 1 < n ? ' ' : '\n');
    }
    assert(seg.all_prod().len == n);
}
