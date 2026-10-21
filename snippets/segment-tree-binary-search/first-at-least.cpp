// max のセグメント木で「位置 l 以降で初めて x 以上」「位置 r より前で最後に x 以上」を探す
// 入力：N Q、A_0 … A_{N-1}、続く Q 行は「0 p v」（A_p = v）か「1 l x」（l 以降で初めて A_i ≥ x の i、なければ N）
//       か「2 r x」（r より前で最後に A_i ≥ x の i、なければ -1）。添字は 0-indexed
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

long long op(long long a, long long b) { return max(a, b); }
long long e() { return LLONG_MIN; }  // max の単位元

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    atcoder::segtree<long long, op, e> seg(a);
    for (int i = 0; i < q; i++) {
        int t;
        long long y, x;
        cin >> t >> y >> x;
        if (t == 0) {
            seg.set(y, x);
            a[y] = x;
            continue;
        }
        long long res, expected;
        if (t == 1) {
            int l = y;
            // --8<-- [start:core]
            // l 以降で初めて A_i ≥ x になる i（なければ n）
            // f は「まだ見つかっていない」間だけ真。f(e()) = (LLONG_MIN < x) は真
            int r = seg.max_right(l, [&](long long v) { return v < x; });
            // [l, r) はすべて x 未満で、r < n なら A_r ≥ x
            // --8<-- [end:core]
            res = r;
            expected = n;
            for (int j = n - 1; j >= l; j--) if (a[j] >= x) expected = j;
        } else {
            int r = y;
            // --8<-- [start:left]
            // r より前で最後に A_i ≥ x になる i（なければ -1）
            int l = seg.min_left(r, [&](long long v) { return v < x; });
            int idx = l - 1;  // [l, r) はすべて x 未満。犯人は 1 つ左の l - 1
            // --8<-- [end:left]
            res = idx;
            expected = -1;
            for (int j = 0; j < r; j++) if (a[j] >= x) expected = j;
        }
        assert(res == expected);
        cout << res << '\n';
    }
}
