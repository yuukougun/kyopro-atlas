// 多角形の面積の 2 倍（符号付き）と、線分の交差判定。
// 入力：N と N 頂点（順に並ぶ）、続けて M と M 行の「ax ay bx by cx cy dx dy」。
// 出力：面積の 2 倍（反時計回りなら正）、各行で線分 AB と CD が共有点を持てば Yes。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
    bool operator<(const Point& o) const { return tie(x, y) < tie(o.x, o.y); }
};
long long cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
int ccw(const Point& p, const Point& q, const Point& r) {
    long long c = cross(q - p, r - p);
    return (c > 0) - (c < 0);
}

// --8<-- [start:area]
// 頂点を順に並べた多角形の面積の 2 倍。反時計回りなら正、時計回りなら負
long long area2(const vector<Point>& p) {
    int n = p.size();
    __int128 s = 0;  // 各項は |座標| ≤ 10^9 で 2×10^18 まで。途中の和は long long を超えうる
    for (int i = 0; i < n; i++) s += cross(p[i], p[(i + 1) % n]);
    return (long long)s;  // 単純な多角形なら |2S| ≤ 8×10^18 で収まる
}
// --8<-- [end:area]

// --8<-- [start:intersect]
// 線分 AB と CD が共有点を持つか（端点で接する・重なる場合も true）
bool intersect(Point a, Point b, Point c, Point d) {
    int d1 = ccw(a, b, c), d2 = ccw(a, b, d);
    int d3 = ccw(c, d, a), d4 = ccw(c, d, b);
    if (d1 == 0 && d2 == 0 && d3 == 0 && d4 == 0) {
        // 4 点が一直線上：直線に沿った順（x、同じなら y の順）で区間が重なるか
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(b < c) && !(d < a);  // max(a, c) ≤ min(b, d)
    }
    return d1 * d2 <= 0 && d3 * d4 <= 0;  // 互いに相手の直線の両側（または上）にある
}
// --8<-- [end:intersect]

int main() {
    int n;
    cin >> n;
    assert(n >= 3);
    vector<Point> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    cout << area2(p) << '\n';
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        cout << (intersect(a, b, c, d) ? "Yes" : "No") << '\n';
    }
}
