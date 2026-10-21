// 0/1 の列の和のセグメント木で、位置 l 以降の K 番目の 1 を探す
// 入力：N Q、B_0 … B_{N-1}（0 か 1）、続く Q 行は「0 p v」（B_p = v）か「1 l k」（l 以降の k 番目の 1 の位置、なければ -1。k ≥ 1）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

int op(int a, int b) { return a + b; }
int e() { return 0; }

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    atcoder::segtree<int, op, e> seg(b);
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 0) {
            seg.set(x, y);
            b[x] = y;
            continue;
        }
        int l = x, k = y;
        // --8<-- [start:core]
        // [l, r) の 1 の個数が k 未満である最大の r を探す（k ≥ 1 なので f(e()) = (0 < k) は真）
        int r = seg.max_right(l, [&](int s) { return s < k; });
        // r < n なら閉区間 [l, r] にちょうど k 個の 1 があり、B_r が k 番目の 1。r == n なら k 個ない
        int pos = (r < n ? r : -1);
        // --8<-- [end:core]
        int expected = -1, cnt = 0;
        for (int j = l; j < n; j++) {
            cnt += b[j];
            if (b[j] == 1 && cnt == k) { expected = j; break; }
        }
        assert(pos == expected);
        cout << pos << '\n';
    }
}
