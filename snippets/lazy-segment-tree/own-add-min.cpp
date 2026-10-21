// 遅延セグメント木を自作する（再帰で書く。区間加算・区間最小値）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」か「1 l r」。乱数の試験も最後に行う
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;

// --8<-- [start:core]
struct LazySegTree {
    int size;
    vector<long long> d;   // d[k]：ノード k の区間の最小値（k より上の保留中の作用を除く）
    vector<long long> lz;  // lz[k]：d[k] には反映済みで、子にはまだ配っていない加算
    LazySegTree(const vector<long long>& a) : size(1) {
        while (size < (int)a.size()) size *= 2;
        d.assign(2 * size, INF);  // 余りの葉は単位元
        lz.assign(size, 0);       // 保留は内部ノードだけが持つ
        for (int i = 0; i < (int)a.size(); i++) d[size + i] = a[i];
        for (int k = size - 1; k >= 1; k--) d[k] = min(d[2 * k], d[2 * k + 1]);
    }
    void all_apply(int k, long long f) {  // ノード k の区間全体に f を作用させる
        d[k] += f;
        if (k < size) lz[k] += f;  // 内部ノードなら、子に配る分として保留する
    }
    void push(int k) {  // 保留を両方の子へ降ろす
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = 0;
    }
    // ノード k は区間 [kl, kr) を受け持つ
    void apply(int l, int r, long long f, int k, int kl, int kr) {
        if (r <= kl || kr <= l) return;                          // 重ならない
        if (l <= kl && kr <= r) { all_apply(k, f); return; }     // すっぽり入る
        push(k);                                                 // 一部だけ重なる：先に降ろす
        int m = (kl + kr) / 2;
        apply(l, r, f, 2 * k, kl, m);
        apply(l, r, f, 2 * k + 1, m, kr);
        d[k] = min(d[2 * k], d[2 * k + 1]);                      // 子から作り直す
    }
    long long prod(int l, int r, int k, int kl, int kr) {
        if (r <= kl || kr <= l) return INF;
        if (l <= kl && kr <= r) return d[k];
        push(k);
        int m = (kl + kr) / 2;
        return min(prod(l, r, 2 * k, kl, m), prod(l, r, 2 * k + 1, m, kr));
    }
    void apply(int l, int r, long long f) { apply(l, r, f, 1, 0, size); }
    long long prod(int l, int r) { return prod(l, r, 1, 0, size); }
};
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    LazySegTree seg(a);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long x;
            cin >> x;
            seg.apply(l, r, x);
        } else {
            cout << seg.prod(l, r) << '\n';
        }
    }
    // 乱数で素朴な方法と比べる
    mt19937 rng(20261021);
    for (int iter = 0; iter < 200; iter++) {
        int m = rng() % 20 + 1;
        vector<long long> b(m);
        for (auto& x : b) x = (long long)(rng() % 21) - 10;
        LazySegTree t(b);
        for (int j = 0; j < 100; j++) {
            int l = rng() % (m + 1), r = rng() % (m + 1);
            if (l > r) swap(l, r);
            if (rng() % 2) {
                long long x = (long long)(rng() % 21) - 10;
                t.apply(l, r, x);
                for (int p = l; p < r; p++) b[p] += x;
            } else {
                long long expected = INF;
                for (int p = l; p < r; p++) expected = min(expected, b[p]);
                assert(t.prod(l, r) == expected);
            }
        }
    }
}
