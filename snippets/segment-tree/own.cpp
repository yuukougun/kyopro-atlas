// セグメント木を自作する（非再帰。ACL の segtree と同じ配置・同じ名前）
// 例として、可換でない演算（1 次関数の合成）を載せ、素朴な計算と照らし合わせる。
// 最後に乱数で、max_right・min_left・all_prod を素朴な方法と比べる
// 入力：N Q、続く N 行に c_i d_i（f_i(x) = c_i x + d_i）、
//       続く Q 行は「0 p c d」（f_p を差し替える）か「1 l r x」（f_{r-1}(…f_l(x)…) mod 998244353 を出力）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size;
    vector<S> d;  // d[k]：ノード k が受け持つ区間の総積。葉 i は d[size + i]
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}  // 全要素が e()
    explicit SegTree(const vector<S>& a) : n(a.size()), size(1) {
        while (size < n) size *= 2;
        d.assign(2 * size, e());  // 余りの葉は単位元
        for (int i = 0; i < n; i++) d[size + i] = a[i];
        for (int k = size - 1; k >= 1; k--) d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    void set(int p, S x) {  // 葉を書き換え、根まで作り直す
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for (p /= 2; p >= 1; p /= 2) d[p] = op(d[2 * p], d[2 * p + 1]);
    }
    S get(int p) const {
        assert(0 <= p && p < n);
        return d[size + p];
    }
    S prod(int l, int r) const {  // [l, r) の総積。l == r なら e()
        assert(0 <= l && l <= r && r <= n);
        S sL = e(), sR = e();  // 左端から集めた積・右端から集めた積
        for (l += size, r += size; l < r; l /= 2, r /= 2) {
            if (l & 1) sL = op(sL, d[l++]);  // l が右の子なら使って右隣へ
            if (r & 1) sR = op(d[--r], sR);  // r - 1 が左の子なら使って左隣へ
        }
        return op(sL, sR);  // 左の積を先に置く
    }
    S all_prod() const { return d[1]; }
    // f(prod(l, r)) が真で、r == n か f(prod(l, r + 1)) が偽になる r（f(e()) が真であること）
    template <class G> int max_right(int l, G f) const {
        assert(0 <= l && l <= n && f(e()));
        if (l == n) return n;
        l += size;
        S sm = e();  // 元の l から、今のノードの左端の手前までの総積
        do {
            while (l % 2 == 0) l /= 2;  // 登る段階：左の子の間は親へ（左端が同じ）
            if (!f(op(sm, d[l]))) {     // 掛けると偽：境目はこのノードの中にある
                while (l < size) {      // 降りる段階：左の子を掛けても真なら、掛けて右の子へ
                    l = 2 * l;
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);  // 掛けても真：掛けて右隣のノードへ
            l++;
        } while ((l & -l) != l);  // l が 2 の冪になったら、木の右端まで掛け終えた
        return n;
    }
    // f(prod(l, r)) が真で、l == 0 か f(prod(l - 1, r)) が偽になる l（f(e()) が真であること）
    template <class G> int min_left(int r, G f) const {
        assert(0 <= r && r <= n && f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();  // 今のノードの右端から、元の r の手前までの総積
        do {
            r--;
            while (r > 1 && r % 2 == 1) r /= 2;  // 右の子の間は親へ（右端が同じ）
            if (!f(op(d[r], sm))) {              // 左から掛ける（可換でない演算のため）
                while (r < size) {
                    r = 2 * r + 1;
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
// --8<-- [end:core]

const long long MOD = 998244353;
struct F { long long c, d; };  // x ↦ c x + d
F op(F f, F g) { return {f.c * g.c % MOD, (f.d * g.c + g.d) % MOD}; }  // f を施してから g
F e() { return {1, 0}; }  // 恒等写像

// 乱数の試験に使う 2 つのモノイド
// (1) 和（値は 0 以上）：max_right・min_left に「和が w 以下」を渡し、境目を素朴に求めて比べる
long long op_add(long long a, long long b) { return a + b; }
long long e_add() { return 0; }
// (2) 昇順の判定（可換でない）：区間が広義の昇順か。左右を取り違えると max_right・min_left が誤る
struct Run { long long first, last; bool sorted, empty; };
Run op_run(Run x, Run y) {
    if (x.empty) return y;
    if (y.empty) return x;
    return {x.first, y.last, x.sorted && y.sorted && x.last <= y.first, false};
}
Run e_run() { return {0, 0, true, true}; }

void random_test() {
    mt19937 rng(20261029);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 13;  // 長さ 0 と、2 の冪でない長さを含める
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 6;
        SegTree<long long, op_add, e_add> sum(a);
        vector<Run> runs(n);
        for (int i = 0; i < n; i++) runs[i] = {a[i], a[i], true, false};
        SegTree<Run, op_run, e_run> run(runs);
        long long total = 0;
        for (long long x : a) total += x;
        assert(sum.all_prod() == total);
        SegTree<long long, op_add, e_add> zero(n);  // 全要素が e() の木
        assert(zero.all_prod() == 0 && zero.prod(0, n) == 0);
        for (int l = 0; l <= n; l++) {
            long long w = rng() % 12;
            auto f = [&](long long s) { return s <= w; };
            int r = l;  // 素朴に右へ伸ばす
            long long s = 0;
            while (r < n && s + a[r] <= w) s += a[r++];
            assert(sum.max_right(l, f) == r);
            int r2 = min(l + 1, n);  // 昇順のまま右へ伸ばせる最大の r（1 要素の区間は昇順）
            while (r2 < n && a[r2 - 1] <= a[r2]) r2++;
            assert(run.max_right(l, [](Run x) { return x.sorted; }) == r2);
        }
        for (int r = 0; r <= n; r++) {
            long long w = rng() % 12;
            auto f = [&](long long s) { return s <= w; };
            int l = r;  // 素朴に左へ伸ばす
            long long s = 0;
            while (l > 0 && s + a[l - 1] <= w) s += a[--l];
            assert(sum.min_left(r, f) == l);
            int l2 = max(r - 1, 0);  // 昇順のまま左へ伸ばせる最小の l
            while (l2 > 0 && a[l2 - 1] <= a[l2]) l2--;
            assert(run.min_left(r, [](Run x) { return x.sorted; }) == l2);
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<F> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].c >> a[i].d;
    SegTree<F, op, e> seg(a);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long c, d;
            cin >> p >> c >> d;
            seg.set(p, {c, d});
            a[p] = {c, d};
            assert(seg.get(p).c == c && seg.get(p).d == d);
        } else {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            F f = seg.prod(l, r);
            long long res = (f.c * x + f.d) % MOD;
            long long expected = x;  // 素朴に左から順に施す
            for (int j = l; j < r; j++) expected = (a[j].c * expected + a[j].d) % MOD;
            assert(res == expected);
            cout << res << '\n';
        }
    }
    random_test();
}
