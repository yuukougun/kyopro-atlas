// 双対セグメント木：区間加算・一点取得（加算は順序を入れ替えても同じなので push が要らない）
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r x」（[l, r) に x を加える）か「1 p」（A_p を出力）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct DualSegTree {
    int size;
    vector<long long> lz;  // lz[k]：ノード k の区間全体に加えた量（葉 k = size + p も使う）
    DualSegTree(int n) : size(1) {
        while (size < n) size *= 2;
        lz.assign(2 * size, 0);
    }
    void apply(int l, int r, long long x) {  // [l, r) に x を加える
        for (l += size, r += size; l < r; l /= 2, r /= 2) {
            if (l & 1) lz[l++] += x;
            if (r & 1) lz[--r] += x;
        }
    }
    long long get(int p) {  // 葉から根までの量を集める
        long long res = 0;
        for (int k = p + size; k >= 1; k /= 2) res += lz[k];
        return res;
    }
};
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    DualSegTree seg(n);
    vector<long long> naive = a;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            seg.apply(l, r, x);
            for (int j = l; j < r; j++) naive[j] += x;
        } else {
            int p;
            cin >> p;
            long long res = a[p] + seg.get(p);
            assert(res == naive[p]);
            cout << res << '\n';
        }
    }
}
