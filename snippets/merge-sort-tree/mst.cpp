// マージソート木：区間 [l, r) の x 以下の要素の個数・和と、区間の K 番目に小さい値
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」（x 以下の個数と和を出力）か「1 l r k」（k 番目に小さい値を出力。k は 0-indexed）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct MergeSortTree {
    int size = 1;                     // 葉の数（N 以上の最小の 2 の冪）
    vector<vector<long long>> val;    // val[k]：ノード k の区間の要素を昇順に並べた列
    vector<vector<long long>> acc;    // acc[k][j]：val[k] の先頭 j 個の和（acc[k][0] = 0）

    MergeSortTree(const vector<long long>& a) {
        int n = a.size();
        while (size < n) size *= 2;
        val.assign(2 * size, {});
        acc.assign(2 * size, {});
        for (int i = 0; i < n; i++) val[size + i] = {a[i]};  // 余りの葉は空の列
        for (int k = size - 1; k >= 1; k--) {                 // 子の 2 本の列をマージする
            const auto& lc = val[2 * k];
            const auto& rc = val[2 * k + 1];
            val[k].resize(lc.size() + rc.size());
            merge(lc.begin(), lc.end(), rc.begin(), rc.end(), val[k].begin());
        }
        for (int k = 1; k < 2 * size; k++) {
            acc[k].assign(val[k].size() + 1, 0);
            for (int j = 0; j < (int)val[k].size(); j++) acc[k][j + 1] = acc[k][j] + val[k][j];
        }
    }

    // [l, r) の x 以下の要素の {個数, 和}
    pair<int, long long> count_sum_le(int l, int r, long long x) const {
        int cnt = 0;
        long long sum = 0;
        auto use = [&](int k) {  // ノード k の列で x 以下の個数を二分探索で数える
            int j = upper_bound(val[k].begin(), val[k].end(), x) - val[k].begin();
            cnt += j;
            sum += acc[k][j];
        };
        for (l += size, r += size; l < r; l /= 2, r /= 2) {  // セグメント木と同じ区間の分け方
            if (l & 1) use(l++);
            if (r & 1) use(--r);
        }
        return {cnt, sum};
    }
};
// --8<-- [end:core]

// --8<-- [start:kth]
// [l, r) の k 番目（0-indexed）に小さい値。0 <= k < r - l を仮定する
// 「x 以下が k + 1 個以上」になる最小の x を、全体のソート済みの列 val[1] の添字で二分探索する
long long kth_smallest(const MergeSortTree& t, int l, int r, int k) {
    const auto& all = t.val[1];
    int ng = -1, ok = all.size() - 1;  // all[ok] 以下は k + 1 個以上、all[ng] 以下は k 個以下
    while (ok - ng > 1) {
        int mid = (ng + ok) / 2;
        if (t.count_sum_le(l, r, all[mid]).first >= k + 1) ok = mid;
        else ng = mid;
    }
    return all[ok];
}
// --8<-- [end:kth]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    MergeSortTree t(a);
    for (int i = 0; i < q; i++) {
        int type, l, r;
        long long x;
        cin >> type >> l >> r >> x;
        if (type == 0) {
            auto [cnt, sum] = t.count_sum_le(l, r, x);
            int c2 = 0;  // 素朴な方法で確かめる
            long long s2 = 0;
            for (int j = l; j < r; j++) if (a[j] <= x) c2++, s2 += a[j];
            assert(cnt == c2 && sum == s2);
            cout << cnt << ' ' << sum << '\n';
        } else {
            long long v = kth_smallest(t, l, r, x);
            vector<long long> b(a.begin() + l, a.begin() + r);
            sort(b.begin(), b.end());
            assert(v == b[x]);
            cout << v << '\n';
        }
    }
}
