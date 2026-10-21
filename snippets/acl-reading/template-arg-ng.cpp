#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;
using namespace atcoder;

struct S {
    long long sum;
    int len;
};
S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }
using F = long long;
// --8<-- [start:core]
S mapping(S x, F f) { return {x.sum + f * x.len, x.len}; }  // 引数の順が逆（正しくは mapping(F f, S x)）
// --8<-- [end:core]
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(3);
    cout << seg.all_prod().sum << '\n';
}
