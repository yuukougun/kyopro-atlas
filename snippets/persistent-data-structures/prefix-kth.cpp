// 接頭辞ごとの版：版 i は A_0 … A_{i-1} の値の個数を持つセグメント木。
// [l, r) の値の分布は「版 r − 版 l」なので、K 番目に小さい値と x 以下の個数がオンラインで O(log N)
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 l r k」（[l, r) で k 番目（0-indexed）に小さい値）か「1 l r x」（[l, r) の x 以下の個数）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct PrefixVersions {
    int sz;                   // 座標圧縮した値の種類数（葉の区間は [0, sz)）
    vector<int> lc{0}, rc{0}, cnt{0};  // ノード 0 は空の木
    vector<int> root;         // root[i]：版 i（A の先頭 i 個）の根
    vector<long long> vals;   // 圧縮前の値（昇順）
    PrefixVersions(const vector<long long>& a) {
        vals = a;
        ranges::sort(vals);
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        sz = (int)vals.size();
        root.push_back(0);
        for (long long x : a) {
            int c = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
            root.push_back(add(root.back(), 0, sz, c));
        }
    }
    int add(int t, int kl, int kr, int c) {  // 版 t の値 c の個数を 1 増やした版
        int l = lc[t], r = rc[t], s = cnt[t] + 1;
        if (kr - kl > 1) {
            int mid = (kl + kr) / 2;
            if (c < mid) l = add(l, kl, mid, c);
            else r = add(r, mid, kr, c);
        }
        lc.push_back(l); rc.push_back(r); cnt.push_back(s);
        return (int)cnt.size() - 1;
    }
    long long kth(int l, int r, int k) const {  // [l, r) で k 番目（0-indexed）に小さい値
        int u = root[r], v = root[l], kl = 0, kr = sz;
        while (kr - kl > 1) {
            int mid = (kl + kr) / 2;
            int left = cnt[lc[u]] - cnt[lc[v]];  // [l, r) のうち値が [kl, mid) にある個数
            if (k < left) { u = lc[u]; v = lc[v]; kr = mid; }
            else { k -= left; u = rc[u]; v = rc[v]; kl = mid; }
        }
        return vals[kl];
    }
    int count_le(int l, int r, long long x) const {  // [l, r) で x 以下の個数
        int c = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());  // 圧縮後 [0, c) が x 以下
        return count(root[r], 0, sz, c) - count(root[l], 0, sz, c);
    }
    int count(int t, int kl, int kr, int c) const {  // 版 t で値が [0, c) にある個数
        if (t == 0 || c <= kl) return 0;
        if (kr <= c) return cnt[t];
        int mid = (kl + kr) / 2;
        return count(lc[t], kl, mid, c) + count(rc[t], mid, kr, c);
    }
};
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    PrefixVersions pv(a);
    for (int i = 0; i < q; i++) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 0) {
            int k;
            cin >> k;
            assert(0 <= k && k < r - l);
            long long ans = pv.kth(l, r, k);
            vector<long long> b(a.begin() + l, a.begin() + r);  // 素朴な方法と比べる
            ranges::sort(b);
            assert(b[k] == ans);
            cout << ans << '\n';
        } else {
            long long x;
            cin >> x;
            int ans = pv.count_le(l, r, x);
            assert(ans == count_if(a.begin() + l, a.begin() + r, [&](long long y) { return y <= x; }));
            cout << ans << '\n';
        }
    }
}
