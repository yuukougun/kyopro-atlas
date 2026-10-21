// 長方形の和集合の面積：x の順に走査し、y の軸に区間加算・（最小値, 最小値をとる長さ）の遅延セグメント木
// 入力：N、続く N 行に l d r u（長方形 [l, r) × [d, u)、l < r かつ d < u）。面積を出力
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

// --8<-- [start:core]
struct S { int mn; long long len; };  // 区間の重なりの数の最小値と、最小値をとる部分の長さ
S op(S a, S b) {
    if (a.mn != b.mn) return a.mn < b.mn ? a : b;
    return {a.mn, a.len + b.len};
}
S e() { return {1 << 30, 0}; }
S mapping(int f, S s) { return {s.mn + f, s.len}; }
int composition(int f, int g) { return f + g; }
int id() { return 0; }

struct Rect { long long l, d, r, u; };  // [l, r) × [d, u)

long long union_area(const vector<Rect>& rs) {
    vector<long long> ys;
    for (auto& r : rs) { ys.push_back(r.d); ys.push_back(r.u); }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = max(0, (int)ys.size() - 1);  // 葉 i は y の帯 [ys[i], ys[i+1])
    vector<S> init(m);
    for (int i = 0; i < m; i++) init[i] = {0, ys[i + 1] - ys[i]};
    atcoder::lazy_segtree<S, op, e, int, mapping, composition, id> seg(init);
    long long total = m > 0 ? ys[m] - ys[0] : 0;

    // イベント (x, d, u, ±1)：左辺で +1、右辺で −1
    vector<tuple<long long, long long, long long, int>> evs;
    for (auto& r : rs) {
        evs.push_back({r.l, r.d, r.u, +1});
        evs.push_back({r.r, r.d, r.u, -1});
    }
    sort(evs.begin(), evs.end());
    auto yid = [&](long long y) { return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()); };
    long long area = 0;
    for (int i = 0; i < (int)evs.size(); i++) {
        auto [x, d, u, f] = evs[i];
        seg.apply(yid(d), yid(u), f);
        if (i + 1 < (int)evs.size()) {
            S all = seg.all_prod();
            long long uncovered = (all.mn == 0) ? all.len : 0;  // 重なりが 0 の長さ
            area += (total - uncovered) * (get<0>(evs[i + 1]) - x);  // 次のイベントまでの帯
        }
    }
    return area;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<Rect> rs(n);
    for (auto& r : rs) cin >> r.l >> r.d >> r.r >> r.u;
    long long ans = union_area(rs);
    // 座標が小さいときは、単位の正方形を 1 つずつ数えて照らし合わせる
    long long mx = 0;
    for (auto& r : rs) mx = max({mx, r.r, r.u});
    if (mx <= 50) {
        long long naive = 0;
        for (long long x = 0; x < mx; x++) {
            for (long long y = 0; y < mx; y++) {
                bool in = false;
                for (auto& r : rs) in |= (r.l <= x && x < r.r && r.d <= y && y < r.u);
                naive += in;
            }
        }
        assert(ans == naive);
    }
    cout << ans << '\n';
}
