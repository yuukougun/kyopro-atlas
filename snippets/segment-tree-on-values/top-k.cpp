// 値を添字にしたセグメント木に（個数, 和）を載せ、小さい方から K 個の和を max_right で求める
// 入力：Q、続く Q 行は「1 x」（x を追加）・「2 x」（x を 1 個削除。x はある）・「3 k」（小さい方から k 個の和を出力。k は個数以下）
// クエリをすべて先に読み、追加される値を座標圧縮する（オフライン）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
struct S {
    long long cnt, sum;  // 区間にある値の個数と和
};
S op(S a, S b) { return {a.cnt + b.cnt, a.sum + b.sum}; }
S e() { return {0, 0}; }

// 小さい方から k 個の和（0 <= k <= 全体の個数）。vals[i] は添字 i の値
long long smallest_k_sum(atcoder::segtree<S, op, e>& seg, const vector<long long>& vals, long long k) {
    // [0, r) の個数が k 以下となる最大の r。f(e()) = true が要るので「< k」ではなく「<= k」
    int r = seg.max_right(0, [&](S s) { return s.cnt <= k; });
    S left = seg.prod(0, r);
    long long rest = k - left.cnt;  // 境界の値 vals[r] から取る個数（vals[r] の個数より少ない）
    if (rest == 0) return left.sum;
    return left.sum + rest * vals[r];
}
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    vector<int> t(q);
    vector<long long> x(q);
    for (int i = 0; i < q; i++) cin >> t[i] >> x[i];

    vector<long long> vals;
    for (int i = 0; i < q; i++) if (t[i] == 1) vals.push_back(x[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    atcoder::segtree<S, op, e> seg(m);

    multiset<long long> naive;  // 素朴な方法で確かめる
    for (int i = 0; i < q; i++) {
        if (t[i] == 3) {
            long long res = smallest_k_sum(seg, vals, x[i]);
            long long expected = 0;
            auto it = naive.begin();
            for (long long j = 0; j < x[i]; j++, it++) expected += *it;
            assert(res == expected);
            cout << res << '\n';
            continue;
        }
        int p = lower_bound(vals.begin(), vals.end(), x[i]) - vals.begin();
        long long d = (t[i] == 1 ? 1 : -1);
        S cur = seg.get(p);  // ACL の segtree は set だけなので、読んでから足して書き戻す
        seg.set(p, {cur.cnt + d, cur.sum + d * x[i]});
        if (t[i] == 1) naive.insert(x[i]);
        else naive.erase(naive.find(x[i]));
    }
}
