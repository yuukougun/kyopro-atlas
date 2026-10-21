#include <bits/stdc++.h>
using namespace std;

using P = pair<long long, long long>;

// --8<-- [start:circumcenter]
// a・b・c を通る円の中心（外心）。3 点が一直線上なら外接円はないので nullopt
optional<pair<long double, long double>> circumcenter(P a, P b, P c) {
    long long bx = b.first - a.first, by = b.second - a.second;
    long long cx = c.first - a.first, cy = c.second - a.second;
    long long cross = bx * cy - by * cx;  // 外積。0 なら一直線上（整数で判定する）
    if (cross == 0) return nullopt;
    long double d = 2.0L * cross;
    long double b2 = (long double)bx * bx + (long double)by * by;
    long double c2 = (long double)cx * cx + (long double)cy * cy;
    long double ux = (cy * b2 - by * c2) / d;
    long double uy = (bx * c2 - cx * b2) / d;
    return pair{a.first + ux, a.second + uy};
}
// --8<-- [end:circumcenter]

// 中心 (x, y) から最も遠い点までの距離の 2 乗
long double far2(const vector<P>& p, long double x, long double y) {
    long double m = 0;
    for (auto [px, py] : p) m = max(m, (px - x) * (px - x) + (py - y) * (py - y));
    return m;
}

// --8<-- [start:core]
// 候補を全部試す O(N^4)：2 点を直径とする円の中心（中点）と、3 点の外心
long double enclose_enum(const vector<P>& p) {
    int n = p.size();
    long double best = far2(p, p[0].first, p[0].second);  // N = 1 なら 0
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long double mx = (p[i].first + p[j].first) / 2.0L;
            long double my = (p[i].second + p[j].second) / 2.0L;
            best = min(best, far2(p, mx, my));
            for (int k = j + 1; k < n; k++) {
                auto o = circumcenter(p[i], p[j], p[k]);
                if (o) best = min(best, far2(p, o->first, o->second));
            }
        }
    }
    return sqrtl(best);
}
// --8<-- [end:core]

// --8<-- [start:welzl]
// Welzl の乱択（点をランダムに並べ替えると期待 O(N)）
long double enclose_welzl(vector<P> p, mt19937& rng) {
    shuffle(p.begin(), p.end(), rng);
    long double x = p[0].first, y = p[0].second, r2 = 0;
    auto outside = [&](P q) {
        long double dx = q.first - x, dy = q.second - y;
        // 誤差で周上の点を外と判定しないよう、相対と絶対の小さな幅を足す
        return dx * dx + dy * dy > r2 * (1 + 1e-12L) + 1e-12L;
    };
    auto set_circle = [&](long double cx, long double cy, P q) {
        x = cx, y = cy;
        r2 = (q.first - x) * (q.first - x) + (q.second - y) * (q.second - y);
    };
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (!outside(p[i])) continue;
        set_circle(p[i].first, p[i].second, p[i]);  // p[i] を周上に持つ最小の円
        for (int j = 0; j < i; j++) {
            if (!outside(p[j])) continue;
            set_circle((p[i].first + p[j].first) / 2.0L,  // p[i] と p[j] が周上
                       (p[i].second + p[j].second) / 2.0L, p[i]);
            for (int k = 0; k < j; k++) {
                if (!outside(p[k])) continue;
                auto o = circumcenter(p[i], p[j], p[k]);  // 3 点が周上
                if (o) set_circle(o->first, o->second, p[i]);
            }
        }
    }
    return sqrtl(r2);
}
// --8<-- [end:welzl]

int main() {
    int n;
    cin >> n;
    vector<P> p(n);
    for (auto& [x, y] : p) cin >> x >> y;
    mt19937 rng(12345);
    long double a = enclose_enum(p), b = enclose_welzl(p, rng);
    assert(fabsl(a - b) < 1e-9L);
    // 乱数の点でも 2 つの方法の答えが一致することを確かめる
    for (int t = 0; t < 200; t++) {
        int m = rng() % 12 + 1;
        vector<P> q(m);
        for (auto& [x, y] : q) x = rng() % 21, y = rng() % 21;
        assert(fabsl(enclose_enum(q) - enclose_welzl(q, rng)) < 1e-9L);
    }
    cout << fixed << setprecision(10) << (double)a << '\n';
}
