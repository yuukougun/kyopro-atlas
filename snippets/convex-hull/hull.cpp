// Andrew 法（monotone chain）の凸包と、凸包の辺上・内部の格子点の数（Pick の定理）。
// 入力：N と N 行の「x y」（|x|, |y| ≤ 10^9 の整数。重複してよい）。
// 出力：一直線上の点を除いた凸包（頂点数と、反時計回りの頂点）、
//       一直線上の点を残した凸包（同じ形）、
//       凸包が面積を持てば「辺上の格子点の数 b と内部の格子点の数 i」、持たなければ「- 周上と内部の格子点の総数」。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:point]
struct Point {
    long long x, y;
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
    bool operator<(const Point& o) const { return tie(x, y) < tie(o.x, o.y); }  // x、等しければ y の小さい順
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};
// b が a の左（反時計回りの側）にあれば正
long long cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
// --8<-- [end:point]

// --8<-- [start:core]
// 凸包の頂点を、x が最小（同じなら y が最小）の点から反時計回りに返す。一直線上の点は含めない
vector<Point> convex_hull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());  // 重複点を除く
    int n = p.size();
    if (n <= 2) return p;  // 1 点・2 点はそのまま
    vector<Point> h;
    // 下側：左から右へ。末尾の 2 点と p[i] が左に曲がらない（右に曲がるか一直線）間は末尾を除く
    for (int i = 0; i < n; i++) {
        while (h.size() >= 2 && cross(h.back() - h[h.size() - 2], p[i] - h.back()) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
    // 上側：右から左へ。下側の点（右端まで）は取り除かない
    int lower = h.size();
    for (int i = n - 2; i >= 0; i--) {
        while ((int)h.size() > lower && cross(h.back() - h[h.size() - 2], p[i] - h.back()) <= 0) h.pop_back();
        h.push_back(p[i]);
    }
    h.pop_back();  // 最後に戻ってきた p[0] は先頭と同じ
    return h;
}
// --8<-- [end:core]

// --8<-- [start:collinear]
// 辺の上の点も頂点として残す版。すべての点が一直線上なら、並べた点をそのまま返す
vector<Point> convex_hull_keep_collinear(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    bool all_on_line = true;
    for (int i = 2; i < n; i++) {
        if (cross(p[1] - p[0], p[i] - p[0]) != 0) all_on_line = false;
    }
    if (all_on_line) return p;  // 下側と上側で同じ点を 2 回ずつ拾うのを防ぐ
    vector<Point> h;
    for (int i = 0; i < n; i++) {
        while (h.size() >= 2 && cross(h.back() - h[h.size() - 2], p[i] - h.back()) < 0) h.pop_back();  // 0 では除かない
        h.push_back(p[i]);
    }
    int lower = h.size();
    for (int i = n - 2; i >= 0; i--) {
        if (p[i].x == p[n - 1].x) continue;  // 右端の縦の辺の点は下側で拾い済み
        while ((int)h.size() > lower && cross(h.back() - h[h.size() - 2], p[i] - h.back()) < 0) h.pop_back();
        h.push_back(p[i]);
    }
    h.pop_back();
    return h;
}
// --8<-- [end:collinear]

// --8<-- [start:lattice]
// 頂点が格子点で反時計回りの凸多角形 h（3 頂点以上）について、{辺上の格子点の数 b, 内部の格子点の数 i}
pair<long long, long long> lattice_points(const vector<Point>& h) {
    int k = h.size();
    long long b = 0, area2 = 0;  // area2 は面積の 2 倍
    for (int j = 0; j < k; j++) {
        Point d = h[(j + 1) % k] - h[j];
        b += gcd(llabs(d.x), llabs(d.y));  // 端点を片側だけ数えると、頂点を 2 回数えない
    }
    for (int j = 1; j + 1 < k; j++) {
        area2 += cross(h[j] - h[0], h[j + 1] - h[0]);  // h[0] からの扇形。凸で反時計回りなら各項は正で、和は単調に増える
    }
    long long i = (area2 - b + 2) / 2;  // Pick の定理 2S = 2i + b - 2 を i について解く（割り切れる）
    return {b, i};
}
// --8<-- [end:lattice]

int main() {
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& [x, y] : p) cin >> x >> y;
    auto print = [](const vector<Point>& h) {
        cout << h.size() << '\n';
        for (auto [x, y] : h) cout << x << ' ' << y << '\n';
    };
    vector<Point> h = convex_hull(p);
    print(h);
    print(convex_hull_keep_collinear(p));
    if (h.size() >= 3) {
        auto [b, i] = lattice_points(h);
        cout << b << ' ' << i << '\n';
    } else if (h.size() == 2) {
        Point d = h[1] - h[0];
        cout << "- " << gcd(llabs(d.x), llabs(d.y)) + 1 << '\n';  // 線分の上の格子点
    } else {
        cout << "- 1\n";
    }
}
