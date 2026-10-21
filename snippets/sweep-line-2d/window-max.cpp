// 平面走査と遅延セグメント木：時刻の幅 D・位置の幅 W の枠に入る点の最大数
// 枠は時刻 [s, s + D)・位置 [L, L + W)（s・L は整数で自由に選べる）
// 入力：N D W、続く N 行に t x（0 ≤ x ≤ 10^6 程度。大きいなら座標圧縮する）。答えを出力
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
int op(int a, int b) { return max(a, b); }
int e() { return 0; }  // 個数は 0 以上なので 0 を単位元にしてよい
int mapping(int f, int x) { return x + f; }
int composition(int f, int g) { return f + g; }
int id() { return 0; }

// pts は (時刻 t, 位置 x) の組
int max_in_window(vector<pair<int, int>> pts, int D, int W) {
    sort(pts.begin(), pts.end());  // 時刻の順に走査する
    int m = 0;
    for (auto [t, x] : pts) m = max(m, x + 1);
    // seg[L]：左端を L に置いた位置の枠が覆う、今の時刻の窓の中の点の数
    atcoder::lazy_segtree<int, op, e, int, mapping, composition, id> seg(vector<int>(m, 0));
    int best = 0, j = 0;
    for (int i = 0; i < (int)pts.size(); i++) {
        auto [t, x] = pts[i];
        seg.apply(max(0, x - W + 1), x + 1, +1);  // 左端が [x - W + 1, x] の枠が x を覆う
        while (pts[j].first <= t - D) {  // 時刻の窓 (t - D, t] から出た点を除く
            auto [tj, xj] = pts[j];
            seg.apply(max(0, xj - W + 1), xj + 1, -1);
            j++;
        }
        best = max(best, seg.all_prod());
    }
    return best;
}
// --8<-- [end:core]

int main() {
    int n, d, w;
    cin >> n >> d >> w;
    vector<pair<int, int>> pts(n);
    for (auto& [t, x] : pts) cin >> t >> x;
    int ans = max_in_window(pts, d, w);
    // 素朴な数え上げと照らし合わせる（枠の下端・左端は点の座標にそろえてよい）
    int naive = 0;
    for (auto [s, unused1] : pts) {
        for (auto [unused2, l] : pts) {
            int c = 0;
            for (auto [t, x] : pts) {
                if (s <= t && t < s + d && l <= x && x < l + w) c++;
            }
            naive = max(naive, c);
        }
    }
    assert(ans == naive);
    cout << ans << '\n';
}
