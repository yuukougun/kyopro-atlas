// 方向と直線を、gcd で約分して符号をそろえた整数の組で表す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 方向 (dx, dy) ≠ (0, 0) を正規化する：gcd で割り、dx > 0、dx = 0 なら dy > 0 にそろえる
pair<long long, long long> normalize_dir(long long dx, long long dy) {
    long long g = gcd(dx, dy);  // std::gcd は絶対値で計算し、0 以上を返す
    dx /= g, dy /= g;
    if (dx < 0 || (dx == 0 && dy < 0)) dx = -dx, dy = -dy;
    return {dx, dy};
}

// 異なる 2 点を通る直線を a x + b y + c = 0 で表す。(a, b) を正規化すれば c も一意に決まる
tuple<long long, long long, long long> line_through(long long x1, long long y1, long long x2, long long y2) {
    auto [a, b] = normalize_dir(y2 - y1, x1 - x2);  // (a, b) は方向 (x2 - x1, y2 - y1) に垂直
    long long c = -(a * x1 + b * y1);
    return {a, b, c};
}
// --8<-- [end:core]

int main() {
    assert(normalize_dir(2, -4) == normalize_dir(-1, 2));
    assert(normalize_dir(0, -5) == make_pair(0LL, 1LL));
    assert(line_through(0, 0, 2, 2) == line_through(3, 3, -1, -1));
    // 点の集合から、2 点以上を通る直線の本数を数える
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    set<tuple<long long, long long, long long>> lines;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) lines.insert(line_through(x[i], y[i], x[j], y[j]));
    cout << lines.size() << '\n';
}
