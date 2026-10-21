// BIT 2 本で区間加算・区間和
// 入力：N Q、続く Q 行は「0 l r x」（[l, r) に x を加える）か「1 l r」（[l, r) の和を出力）。初期値はすべて 0
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

// --8<-- [start:core]
struct RangeAddRangeSum {
    int n;
    atcoder::fenwick_tree<long long> b0, b1;  // 差分 d_k を b0 に、k·d_k を b1 に持つ
    RangeAddRangeSum(int n) : n(n), b0(n + 1), b1(n + 1) {}
    void add(int l, int r, long long x) {  // [l, r) に x：d_l += x、d_r -= x
        b0.add(l, x), b1.add(l, x * l);
        b0.add(r, -x), b1.add(r, -x * r);
    }
    long long prefix(int r) {  // a_0 + … + a_{r-1} = r·Σ_{k<r} d_k − Σ_{k<r} k·d_k
        return r * b0.sum(0, r) - b1.sum(0, r);
    }
    long long sum(int l, int r) { return prefix(r) - prefix(l); }
};
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    RangeAddRangeSum st(n);
    vector<long long> naive(n, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            long long x;
            cin >> x;
            st.add(l, r, x);
            for (int j = l; j < r; j++) naive[j] += x;
        } else {
            long long res = st.sum(l, r);
            assert(res == accumulate(naive.begin() + l, naive.begin() + r, 0LL));
            cout << res << '\n';
        }
    }
}
