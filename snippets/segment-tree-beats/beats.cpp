#include <bits/stdc++.h>
using namespace std;

// 区間 chmin・区間 chmax・区間加算・区間和の Segment Tree Beats（0-indexed、半開区間）。
// 入力は Library Checker の Range Chmin Chmax Add Range Sum と同じ形。
// 起動時に小さな乱数の列で愚直な計算と突き合わせる。

const long long INF = numeric_limits<long long>::max() / 4;

struct SegTreeBeats {
    int n;
    // --8<-- [start:node]
    // ノード k が持つもの（最大値の側。最小値の側も対称に持つ）
    vector<long long> mx1, mx2, mn1, mn2, sum, add;  // 最大値・真に 2 番目の最大値・… ・和・保留中の加算
    vector<int> cmx, cmn, len;                        // 最大値の個数・最小値の個数・区間の長さ
    // --8<-- [end:node]

    explicit SegTreeBeats(const vector<long long>& a) : n(a.size()) {
        int m = 4 * max(n, 1);
        mx1.assign(m, -INF); mx2.assign(m, -INF); mn1.assign(m, INF); mn2.assign(m, INF);
        sum.assign(m, 0); add.assign(m, 0); cmx.assign(m, 0); cmn.assign(m, 0); len.assign(m, 0);
        if (n > 0) build(1, 0, n, a);
    }

    void build(int k, int l, int r, const vector<long long>& a) {
        len[k] = r - l;
        if (r - l == 1) {
            mx1[k] = mn1[k] = sum[k] = a[l];
            cmx[k] = cmn[k] = 1;
            return;
        }
        int m = (l + r) / 2;
        build(2 * k, l, m, a);
        build(2 * k + 1, m, r, a);
        pull(k);
    }

    void pull(int k) {
        int p = 2 * k, q = 2 * k + 1;
        sum[k] = sum[p] + sum[q];
        if (mx1[p] == mx1[q]) {
            mx1[k] = mx1[p]; cmx[k] = cmx[p] + cmx[q]; mx2[k] = max(mx2[p], mx2[q]);
        } else if (mx1[p] > mx1[q]) {
            mx1[k] = mx1[p]; cmx[k] = cmx[p]; mx2[k] = max(mx2[p], mx1[q]);
        } else {
            mx1[k] = mx1[q]; cmx[k] = cmx[q]; mx2[k] = max(mx1[p], mx2[q]);
        }
        if (mn1[p] == mn1[q]) {
            mn1[k] = mn1[p]; cmn[k] = cmn[p] + cmn[q]; mn2[k] = min(mn2[p], mn2[q]);
        } else if (mn1[p] < mn1[q]) {
            mn1[k] = mn1[p]; cmn[k] = cmn[p]; mn2[k] = min(mn2[p], mn1[q]);
        } else {
            mn1[k] = mn1[q]; cmn[k] = cmn[q]; mn2[k] = min(mn1[p], mn2[q]);
        }
    }

    void apply_add(int k, long long x) {
        mx1[k] += x; mn1[k] += x;
        if (mx2[k] != -INF) mx2[k] += x;
        if (mn2[k] != INF) mn2[k] += x;
        sum[k] += x * len[k];
        add[k] += x;
    }

    // --8<-- [start:core]
    // 前提：mx2[k] < x < mx1[k]。最大値の要素だけが x に下がる
    void apply_chmin(int k, long long x) {
        sum[k] += (x - mx1[k]) * cmx[k];
        if (mn1[k] == mx1[k]) mn1[k] = x;       // 値が 1 種類：最小値も同じ要素
        else if (mn2[k] == mx1[k]) mn2[k] = x;  // 値が 2 種類：2 番目の最小値が最大値
        mx1[k] = x;
    }

    void chmin(int a, int b, long long x, int k, int l, int r) {
        if (b <= l || r <= a || mx1[k] <= x) return;          // 1. 効かない：止める
        if (a <= l && r <= b && mx2[k] < x) {                  // 2. 最大値だけが変わる：タグ
            apply_chmin(k, x);
            return;
        }
        push(k);                                               // 3. それ以外：子へ
        int m = (l + r) / 2;
        chmin(a, b, x, 2 * k, l, m);
        chmin(a, b, x, 2 * k + 1, m, r);
        pull(k);
    }
    // --8<-- [end:core]

    // 前提：mn1[k] < x < mn2[k]。apply_chmin と対称
    void apply_chmax(int k, long long x) {
        sum[k] += (x - mn1[k]) * cmn[k];
        if (mx1[k] == mn1[k]) mx1[k] = x;
        else if (mx2[k] == mn1[k]) mx2[k] = x;
        mn1[k] = x;
    }

    void chmax(int a, int b, long long x, int k, int l, int r) {
        if (b <= l || r <= a || mn1[k] >= x) return;
        if (a <= l && r <= b && mn2[k] > x) {
            apply_chmax(k, x);
            return;
        }
        push(k);
        int m = (l + r) / 2;
        chmax(a, b, x, 2 * k, l, m);
        chmax(a, b, x, 2 * k + 1, m, r);
        pull(k);
    }

    // --8<-- [start:push]
    // 子へ降りる前に、保留中の加算と、親の最大値・最小値への切り詰めを子に渡す
    void push(int k) {
        for (int c = 2 * k; c <= 2 * k + 1; c++) {
            if (add[k] != 0) apply_add(c, add[k]);
            if (mx1[c] > mx1[k]) apply_chmin(c, mx1[k]);  // 子の 2 番目は親の最大値より小さい
            if (mn1[c] < mn1[k]) apply_chmax(c, mn1[k]);
        }
        add[k] = 0;
    }
    // --8<-- [end:push]

    void range_add(int a, int b, long long x, int k, int l, int r) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            apply_add(k, x);
            return;
        }
        push(k);
        int m = (l + r) / 2;
        range_add(a, b, x, 2 * k, l, m);
        range_add(a, b, x, 2 * k + 1, m, r);
        pull(k);
    }

    long long range_sum(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return sum[k];
        push(k);
        int m = (l + r) / 2;
        return range_sum(a, b, 2 * k, l, m) + range_sum(a, b, 2 * k + 1, m, r);
    }

    // 空区間（a == b）は何もしない・0 を返す
    void chmin(int a, int b, long long x) { if (a < b) chmin(a, b, x, 1, 0, n); }
    void chmax(int a, int b, long long x) { if (a < b) chmax(a, b, x, 1, 0, n); }
    void add_range(int a, int b, long long x) { if (a < b) range_add(a, b, x, 1, 0, n); }
    long long get_sum(int a, int b) { return a < b ? range_sum(a, b, 1, 0, n) : 0; }
};

void self_test() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 12 + 1;
        vector<long long> a(n);
        for (auto& v : a) v = (long long)(rng() % 21) - 10;
        SegTreeBeats seg(a);
        for (int q = 0; q < 200; q++) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            long long x = (long long)(rng() % 21) - 10;
            int t = rng() % 4;
            if (t == 0) { for (int i = l; i < r; i++) a[i] = min(a[i], x); seg.chmin(l, r, x); }
            if (t == 1) { for (int i = l; i < r; i++) a[i] = max(a[i], x); seg.chmax(l, r, x); }
            if (t == 2) { for (int i = l; i < r; i++) a[i] += x; seg.add_range(l, r, x); }
            long long naive = 0;
            for (int i = l; i < r; i++) naive += a[i];
            assert(seg.get_sum(l, r) == naive);
        }
    }
}

int main() {
    self_test();
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    SegTreeBeats seg(a);
    // --8<-- [start:usage]
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 3) {
            cout << seg.get_sum(l, r) << '\n';
            continue;
        }
        long long b;
        cin >> b;
        if (t == 0) seg.chmin(l, r, b);       // a_i ← min(a_i, b)
        if (t == 1) seg.chmax(l, r, b);       // a_i ← max(a_i, b)
        if (t == 2) seg.add_range(l, r, b);   // a_i ← a_i + b
    }
    // --8<-- [end:usage]
}
