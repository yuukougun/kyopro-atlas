// 0/1 列の区間反転と、区間で 1 が連続する最大の長さ
// 入力：N Q、0/1 の文字列、続く Q 行は「0 l r」（[l, r) を反転）か「1 l r」（[l, r) の 1 の最長の連続を出力）
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
struct S {
    int len;
    int pre[2], suf[2], best[2];  // c = 0, 1 について：左端から続く c の長さ・右端まで続く c の長さ・c の最長
};
S op(S x, S y) {
    if (x.len == 0) return y;  // e() とつなぐときは相手をそのまま返す
    if (y.len == 0) return x;
    S z;
    z.len = x.len + y.len;
    for (int c = 0; c < 2; c++) {
        z.pre[c] = x.pre[c] == x.len ? x.len + y.pre[c] : x.pre[c];  // 左が全部 c なら右へつながる
        z.suf[c] = y.suf[c] == y.len ? y.len + x.suf[c] : y.suf[c];
        z.best[c] = max({x.best[c], y.best[c], x.suf[c] + y.pre[c]});  // 境目をまたぐ連続
    }
    return z;
}
S e() { return {0, {0, 0}, {0, 0}, {0, 0}}; }
S mapping(bool flip, S x) {
    if (flip) {  // 0 と 1 の欄を入れ替えるだけ
        swap(x.pre[0], x.pre[1]);
        swap(x.suf[0], x.suf[1]);
        swap(x.best[0], x.best[1]);
    }
    return x;
}
bool composition(bool f, bool g) { return f != g; }  // 2 回の反転は打ち消し合う（XOR）
bool id() { return false; }
S leaf(int c) {  // 1 文字の葉
    S s = e();
    s.len = 1;
    s.pre[c] = s.suf[c] = s.best[c] = 1;
    return s;
}
// --8<-- [end:core]

int main() {
    int n, q;
    string str;
    cin >> n >> q >> str;
    vector<S> init(n);
    vector<int> naive(n);
    for (int i = 0; i < n; i++) {
        naive[i] = str[i] - '0';
        init[i] = leaf(naive[i]);
    }
    atcoder::lazy_segtree<S, op, e, bool, mapping, composition, id> seg(init);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            seg.apply(l, r, true);
            for (int j = l; j < r; j++) naive[j] ^= 1;
        } else {
            int expected = 0, run = 0;
            for (int j = l; j < r; j++) {
                run = naive[j] == 1 ? run + 1 : 0;
                expected = max(expected, run);
            }
            int res = seg.prod(l, r).best[1];
            assert(res == expected);
            cout << res << '\n';
        }
    }
}
