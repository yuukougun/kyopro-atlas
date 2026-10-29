// 遅延セグメント木を自作する（ACL の lazy_segtree と同じ 7 つの部品を受け取る。区間の操作は再帰で書く）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」（[l, r) に x を加える）か「1 l r」（[l, r) の最小値を出力）。
// 区間加算・区間最小値で動かし、最後に乱数で、区間アフィン・区間和（作用が可換でない）と set・get・all_prod も
// 素朴な方法と比べる
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class S, S (*op)(S, S), S (*e)(),
          class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct LazySegTree {
    int n, size, log;
    vector<S> d;   // d[k]：ノード k の区間の総積（k より上の祖先に残る保留を除く）
    vector<F> lz;  // lz[k]：d[k] には施し済みで、子にはまだ配っていない作用（内部ノードだけ）
    LazySegTree() : LazySegTree(0) {}
    explicit LazySegTree(int n) : LazySegTree(vector<S>(n, e())) {}  // 全要素が e()
    explicit LazySegTree(const vector<S>& a) : n(a.size()), size(1), log(0) {
        while (size < n) size *= 2, log++;
        d.assign(2 * size, e());  // 余りの葉は単位元
        lz.assign(size, id());
        for (int i = 0; i < n; i++) d[size + i] = a[i];
        for (int k = size - 1; k >= 1; k--) d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    void all_apply(int k, F f) {  // ノード k の区間全体に f を施す
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);  // 内部ノードなら、保留の後に f を重ねる
    }
    void push(int k) {  // 保留を子へ 1 段降ろす
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
    // ノード k は区間 [kl, kr) を受け持つ
    void apply(int l, int r, F f, int k, int kl, int kr) {
        if (r <= kl || kr <= l) return;                       // 重ならない
        if (l <= kl && kr <= r) { all_apply(k, f); return; }  // すっぽり入る
        push(k);                                              // 一部だけ重なる：子を触る前に降ろす
        int m = (kl + kr) / 2;
        apply(l, r, f, 2 * k, kl, m);
        apply(l, r, f, 2 * k + 1, m, kr);
        d[k] = op(d[2 * k], d[2 * k + 1]);                    // 子から作り直す
    }
    S prod(int l, int r, int k, int kl, int kr) {
        if (r <= kl || kr <= l) return e();
        if (l <= kl && kr <= r) return d[k];
        push(k);
        int m = (kl + kr) / 2;
        return op(prod(l, r, 2 * k, kl, m), prod(l, r, 2 * k + 1, m, kr));  // 左の子を先に結ぶ
    }
    void apply(int l, int r, F f) {  // [l, r) に f を作用させる
        assert(0 <= l && l <= r && r <= n);
        apply(l, r, f, 1, 0, size);
    }
    S prod(int l, int r) {  // [l, r) の総積。l == r なら e()
        assert(0 <= l && l <= r && r <= n);
        return prod(l, r, 1, 0, size);
    }
    S all_prod() const { return d[1]; }
    void set(int p, S x) {  // 葉の祖先を上から push してから書き換え、祖先を下から作り直す
        assert(0 <= p && p < n);
        p += size;
        for (int h = log; h >= 1; h--) push(p >> h);
        d[p] = x;
        for (int h = 1; h <= log; h++) {
            int k = p >> h;
            d[k] = op(d[2 * k], d[2 * k + 1]);
        }
    }
    S get(int p) {  // 葉の祖先を上から push してから読む
        assert(0 <= p && p < n);
        p += size;
        for (int h = log; h >= 1; h--) push(p >> h);
        return d[p];
    }
};
// --8<-- [end:core]

// 区間加算・区間最小値の 7 つの部品
const long long INF = 1LL << 60;
long long op_min(long long x, long long y) { return min(x, y); }
long long e_min() { return INF; }
long long mapping_add(long long f, long long x) { return x + f; }
long long composition_add(long long f, long long g) { return f + g; }
long long id_add() { return 0; }

// 区間アフィン・区間和（mod 998244353）の 7 つの部品。合成の向きを間違えると乱数の試験で見つかる
const long long MOD = 998244353;
struct Sum { long long s, len; };   // 区間の和（mod）と区間の長さ
struct Affine { long long b, c; };  // x ↦ b x + c
Sum op_sum(Sum x, Sum y) { return {(x.s + y.s) % MOD, x.len + y.len}; }
Sum e_sum() { return {0, 0}; }
Sum mapping_affine(Affine f, Sum x) { return {(f.b * x.s + f.c * x.len) % MOD, x.len}; }
Affine composition_affine(Affine f, Affine g) { return {f.b * g.b % MOD, (f.b * g.c + f.c) % MOD}; }  // g の後に f
Affine id_affine() { return {1, 0}; }

void random_test() {
    mt19937 rng(20261029);
    for (int iter = 0; iter < 200; iter++) {
        int m = rng() % 20 + 1;
        // 区間加算・区間最小値
        vector<long long> b(m);
        for (auto& x : b) x = (long long)(rng() % 21) - 10;
        LazySegTree<long long, op_min, e_min, long long, mapping_add, composition_add, id_add> t(b);
        // 区間アフィン・区間和
        vector<long long> c(m);
        vector<Sum> init(m);
        for (int i = 0; i < m; i++) c[i] = rng() % MOD, init[i] = {c[i], 1};
        LazySegTree<Sum, op_sum, e_sum, Affine, mapping_affine, composition_affine, id_affine> u(init);
        LazySegTree<Sum, op_sum, e_sum, Affine, mapping_affine, composition_affine, id_affine> empty(m);
        empty.apply(0, m, {2, 3});  // 全要素が e()（長さ 0）なので、作用しても和は 0 のまま
        assert(empty.all_prod().s == 0 && empty.all_prod().len == 0);
        for (int j = 0; j < 100; j++) {
            int l = rng() % (m + 1), r = rng() % (m + 1);
            if (l > r) swap(l, r);
            int p = rng() % m;
            int type = rng() % 4;
            if (type == 0) {  // 作用
                long long x = (long long)(rng() % 21) - 10;
                t.apply(l, r, x);
                for (int i = l; i < r; i++) b[i] += x;
                Affine f = {(long long)(rng() % MOD), (long long)(rng() % MOD)};
                u.apply(l, r, f);
                for (int i = l; i < r; i++) c[i] = (f.b * c[i] + f.c) % MOD;
            } else if (type == 1) {  // 取得
                long long mn = INF, s = 0;
                for (int i = l; i < r; i++) mn = min(mn, b[i]), s = (s + c[i]) % MOD;
                assert(t.prod(l, r) == mn);
                assert(u.prod(l, r).s == s && u.prod(l, r).len == r - l);
            } else if (type == 2) {  // 一点の書き換え
                long long x = (long long)(rng() % 21) - 10;
                t.set(p, x);
                b[p] = x;
                c[p] = rng() % MOD;
                u.set(p, {c[p], 1});
            } else {  // 一点の取得と全体
                assert(t.get(p) == b[p] && u.get(p).s == c[p]);
                assert(t.all_prod() == *min_element(b.begin(), b.end()));
                long long s = 0;
                for (long long x : c) s = (s + x) % MOD;
                assert(u.all_prod().s == s);
            }
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    LazySegTree<long long, op_min, e_min, long long, mapping_add, composition_add, id_add> seg(a);
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
    random_test();
}
