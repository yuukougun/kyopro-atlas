// 重み付きの最長増加部分列：高さ h_i が狭義増加になるように選ぶとき、重み w_i の和の最大を求める。
// 高さを座標圧縮し、「末尾の高さが v の列の重みの和の最大」を値を添字にしたセグメント木に持つ。
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

long long op(long long x, long long y) { return max(x, y); }
long long e() { return 0; }  // 何も選ばない列の和（重みは 0 以上とする）

int main() {
    int n;
    cin >> n;
    assert(n >= 0);
    vector<long long> h(n), w(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        assert(w[i] >= 0);
    }

    // --8<-- [start:core]
    vector<long long> vals = h;  // 高さの座標圧縮
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();

    atcoder::segtree<long long, op, e> seg(m);  // seg[v]：末尾の高さが vals[v] の列の重みの和の最大
    for (int i = 0; i < n; i++) {
        int v = lower_bound(vals.begin(), vals.end(), h[i]) - vals.begin();
        long long best = seg.prod(0, v) + w[i];   // 高さが h[i] 未満で終わる列の末尾につなぐ（狭義なので [0, v)）
        seg.set(v, max(seg.get(v), best));        // 同じ高さが前にあれば大きい方を残す
    }
    cout << seg.all_prod() << '\n';
    // --8<-- [end:core]
}
