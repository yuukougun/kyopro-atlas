// 自作のセグメント木の max_right（再帰。和のセグメント木で確かめる）
// 入力：N Q、A_0 … A_{N-1}（非負）、続く Q 行は「l w」（[l, r) の和が w 以下である最大の r。w ≥ 0）
#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n, size;
    vector<long long> d;  // d[k] はノード k の区間の和。余りの葉は単位元 0
    explicit SegTree(const vector<long long>& a) : n(a.size()), size(1) {
        while (size < n) size *= 2;
        d.assign(2 * size, 0);
        for (int i = 0; i < n; i++) d[size + i] = a[i];
        for (int k = size - 1; k >= 1; k--) d[k] = d[2 * k] + d[2 * k + 1];
    }
    // --8<-- [start:core]
    // ノード k（区間 [kl, kr)）の中で、累積 sm に足すと f が偽になる最初の葉を返す。なければ -1
    template <class F> int search(int k, int kl, int kr, int l, F& f, long long& sm) const {
        if (kr <= l) return -1;                      // l より左のノードは見ない
        if (l <= kl && f(sm + d[k])) {               // 丸ごと足しても真なら、足して右へ
            sm += d[k];
            return -1;
        }
        if (kr - kl == 1) return kl;                 // 葉で偽になった：ここが境界
        int m = (kl + kr) / 2;
        int res = search(2 * k, kl, m, l, f, sm);   // 左の子を先に見る
        if (res != -1) return res;
        return search(2 * k + 1, m, kr, l, f, sm);
    }
    template <class F> int max_right(int l, F f) const {  // f(0) は真であること
        long long sm = 0;
        int res = search(1, 0, size, l, f, sm);
        return res == -1 ? n : min(res, n);
    }
    // --8<-- [end:core]
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SegTree seg(a);
    for (int i = 0; i < q; i++) {
        int l;
        long long w;
        cin >> l >> w;
        int r = seg.max_right(l, [&](long long s) { return s <= w; });
        int expected = l;
        long long s = 0;
        while (expected < n && s + a[expected] <= w) s += a[expected++];
        assert(r == expected);
        cout << r << '\n';
    }
}
