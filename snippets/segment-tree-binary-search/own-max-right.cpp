// 自作のセグメント木の max_right（再帰。演算は部品で受け取り、和のセグメント木で確かめる）
// 入力：N Q、A_0 … A_{N-1}（非負）、続く Q 行は「l w」（[l, r) の和が w 以下である最大の r。w ≥ 0）
#include <bits/stdc++.h>
using namespace std;

template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {  // 構築はセグメント木のページの自作の SegTree と同じ
    int n, size;
    vector<S> d;  // d[k] はノード k の区間の総積。余りの葉は単位元
    explicit SegTree(const vector<S>& a) : n(a.size()), size(1) {
        while (size < n) size *= 2;
        d.assign(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = a[i];
        for (int k = size - 1; k >= 1; k--) d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    // --8<-- [start:core]
    // ノード k（区間 [kl, kr)）の中で、累積 sm に掛けると f が偽になる最初の葉を返す。なければ -1
    template <class G> int search(int k, int kl, int kr, int l, G& f, S& sm) const {
        if (kr <= l) return -1;                      // l より左のノードは見ない
        if (l <= kl && f(op(sm, d[k]))) {            // 丸ごと掛けても真なら、掛けて右へ
            sm = op(sm, d[k]);
            return -1;
        }
        if (kr - kl == 1) return kl;                 // 葉で偽になった：ここが境界
        int m = (kl + kr) / 2;
        int res = search(2 * k, kl, m, l, f, sm);   // 左の子を先に見る
        if (res != -1) return res;
        return search(2 * k + 1, m, kr, l, f, sm);
    }
    template <class G> int max_right(int l, G f) const {  // f(e()) が真であること
        assert(0 <= l && l <= n && f(e()));
        S sm = e();
        int res = search(1, 0, size, l, f, sm);
        return res == -1 ? n : min(res, n);
    }
    // --8<-- [end:core]
};

long long op_add(long long x, long long y) { return x + y; }
long long e_add() { return 0; }

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SegTree<long long, op_add, e_add> seg(a);
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
