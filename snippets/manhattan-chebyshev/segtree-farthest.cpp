#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

// --8<-- [start:core]
// x+y・−(x+y)・x−y・−(x−y) の 4 つの最大を 1 つの値として持つ
struct S {
    long long a[4];
};
const long long NEG = LLONG_MIN / 4;
S op(S l, S r) {
    S res;
    for (int k = 0; k < 4; k++) res.a[k] = max(l.a[k], r.a[k]);
    return res;
}
S e() { return S{{NEG, NEG, NEG, NEG}}; }
S make(long long x, long long y) { return S{{x + y, -(x + y), x - y, -(x - y)}}; }

// 区間 [l, r) の点のうち (x, y) から最も遠い点までの距離（区間は空でないとする）
long long farthest(atcoder::segtree<S, op, e>& seg, int l, int r, long long x, long long y) {
    S m = seg.prod(l, r);
    return max({m.a[0] - (x + y), m.a[1] + (x + y), m.a[2] - (x - y), m.a[3] + (x - y)});
}
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> px(n), py(n);
    atcoder::segtree<S, op, e> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> px[i] >> py[i];
        seg.set(i, make(px[i], py[i]));
    }
    for (int t = 0; t < q; t++) {
        int type;
        cin >> type;
        if (type == 1) {  // 点 i を (x, y) に動かす
            int i;
            long long x, y;
            cin >> i >> x >> y;
            px[i] = x, py[i] = y;
            seg.set(i, make(x, y));
        } else {  // 区間 [l, r) で (x, y) から最も遠い点
            int l, r;
            long long x, y;
            cin >> l >> r >> x >> y;
            long long ans = farthest(seg, l, r, x, y);
            long long brute = 0;
            for (int i = l; i < r; i++) brute = max(brute, llabs(px[i] - x) + llabs(py[i] - y));
            assert(ans == brute);
            cout << ans << '\n';
        }
    }
}
