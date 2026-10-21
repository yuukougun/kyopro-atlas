// 点の多角形の内外判定。凸多角形は扇形に分けて二分探索（1 点 O(log N)）、一般の多角形は交差数の偶奇（1 点 O(N)）。
// 入力：N と N 行の頂点「x y」（反時計回り。|x|, |y| ≤ 10^9）、Q と Q 行の点「x y」。
// 出力：各点について、凸多角形としての判定と一般の多角形としての判定（2：内部、1：境界、0：外部）を「c g」で。
//       凸多角形としての判定は、多角形が凸（一直線に並ぶ 3 頂点がない）のときだけ意味を持つ。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
};
long long cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
long long dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }

// --8<-- [start:convex]
// p：反時計回りの凸多角形（3 頂点以上、一直線に並ぶ 3 頂点はない）。2：内部、1：境界、0：外部
int contains_convex(const vector<Point>& p, Point q) {
    int n = p.size();
    Point a = q - p[0];
    long long c1 = cross(p[1] - p[0], a), c2 = cross(p[n - 1] - p[0], a);
    if (c1 < 0 || c2 > 0) return 0;  // 扇形の全体（p[0] から見た角）の外
    // 扇形の両端の半直線の上：線分の範囲内なら境界、先なら外部
    if (c1 == 0) return dot(a, a) <= dot(p[1] - p[0], p[1] - p[0]) ? 1 : 0;
    if (c2 == 0) return dot(a, a) <= dot(p[n - 1] - p[0], p[n - 1] - p[0]) ? 1 : 0;
    // cross(p[ok] - p[0], a) ≥ 0、cross(p[ng] - p[0], a) < 0 を保って、q の入る扇形 (ok, ok + 1) を探す
    int ok = 1, ng = n - 1;
    while (ng - ok > 1) {
        int mid = (ok + ng) / 2;
        if (cross(p[mid] - p[0], a) >= 0) ok = mid;
        else ng = mid;
    }
    long long c = cross(p[ok + 1] - p[ok], q - p[ok]);  // 扇形の外側の辺 p[ok] → p[ok+1] のどちら側か
    return c > 0 ? 2 : (c == 0 ? 1 : 0);
}
// --8<-- [end:convex]

// --8<-- [start:general]
// p：辺が交差しない多角形（凹んでいてよい。向きはどちらでもよい）。2：内部、1：境界、0：外部
int contains_general(const vector<Point>& p, Point q) {
    int n = p.size();
    bool in = false;
    for (int i = 0; i < n; i++) {
        Point a = p[i] - q, b = p[(i + 1) % n] - q;  // q を原点に移す
        if (cross(a, b) == 0 && dot(a, b) <= 0) return 1;  // 辺の上
        if (a.y > b.y) swap(a, b);                          // a を下の端点にする
        // q から右へ伸ばした半直線と交わるか。下の端点は含め、上の端点は含めない（頂点を 2 回数えない）
        if (a.y <= 0 && 0 < b.y && cross(a, b) > 0) in = !in;
    }
    return in ? 2 : 0;
}
// --8<-- [end:general]

int main() {
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) cin >> x >> y;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Point r;
        cin >> r.x >> r.y;
        cout << contains_convex(p, r) << ' ' << contains_general(p, r) << '\n';
    }
}
