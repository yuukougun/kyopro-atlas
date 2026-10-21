// 整数座標の点と、外積・内積・ccw（3 点の回り方）。
// 入力：Q と、Q 行の「px py qx qy rx ry」。各行で ccw(p, q, r) を出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:point]
struct Point {
    long long x, y;
    Point operator+(const Point& o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point& o) const { return {x - o.x, y - o.y}; }
};
// 外積：b が a の左（反時計回りの側）にあれば正、右なら負、同じ直線上なら 0
long long cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
// 内積：a と b のなす角が鋭角なら正、直角なら 0、鈍角なら負
long long dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
// --8<-- [end:point]

// --8<-- [start:ccw]
// p → q → r と進むとき、左に曲がれば 1、右に曲がれば -1、一直線上なら 0
int ccw(const Point& p, const Point& q, const Point& r) {
    long long c = cross(q - p, r - p);  // |座標| ≤ 10^9 なら各積は 4×10^18 以下で、差も long long に収まる
    return (c > 0) - (c < 0);           // 値ではなく符号だけを返す（符号どうしは掛けてもあふれない）
}
// --8<-- [end:ccw]

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Point p, a, b;
        cin >> p.x >> p.y >> a.x >> a.y >> b.x >> b.y;
        for (long long v : {p.x, p.y, a.x, a.y, b.x, b.y}) assert(-1000000000 <= v && v <= 1000000000);
        cout << ccw(p, a, b) << '\n';
    }
}
