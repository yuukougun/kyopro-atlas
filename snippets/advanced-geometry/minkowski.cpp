#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};
P operator+(P a, P b) { return {a.x + b.x, a.y + b.y}; }
P operator-(P a, P b) { return {a.x - b.x, a.y - b.y}; }
bool operator<(P a, P b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }
bool operator==(P a, P b) { return a.x == b.x && a.y == b.y; }
long long cross(P a, P b) { return a.x * b.y - a.y * b.x; }

// Andrew 法。反時計回りで、一直線上の点を除いた凸包の頂点を返す
vector<P> convex_hull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n <= 1) return p;
    vector<P> h(2 * n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(h[k - 1] - h[k - 2], p[i] - h[k - 2]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(h[k - 1] - h[k - 2], p[i] - h[k - 2]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k - 1);
    return h;
}

// --8<-- [start:core]
// a, b：凸多角形の頂点（反時計回り、1 点・2 点でもよい）。和の凸多角形の頂点を返す
// （辺の向きが同じなら 1 本にまとめるが、一直線上の頂点が残ることがある）
vector<P> minkowski_sum(vector<P> a, vector<P> b) {
    // 最も下の頂点（同じ高さなら最も左）から始める
    auto start_bottom = [](vector<P>& v) {
        int k = 0;
        for (int i = 1; i < (int)v.size(); i++)
            if (make_pair(v[i].y, v[i].x) < make_pair(v[k].y, v[k].x)) k = i;
        rotate(v.begin(), v.begin() + k, v.end());
    };
    start_bottom(a);
    start_bottom(b);
    int n = a.size(), m = b.size(), i = 0, j = 0;
    vector<P> res;
    while (i < n || j < m) {
        res.push_back(a[i % n] + b[j % m]);
        P ea = a[(i + 1) % n] - a[i % n], eb = b[(j + 1) % m] - b[j % m];
        long long c = cross(ea, eb);
        // 偏角の小さい方の辺を進める（同じ向きなら両方）
        if (j == m || (i < n && c > 0)) i++;
        else if (i == n || c < 0) j++;
        else i++, j++;
    }
    return res;
}
// --8<-- [end:core]

int main() {
    // 小さい乱数の凸多角形で、全組の和の凸包と照らし合わせる
    mt19937 rng(2026);
    for (int it = 0; it < 3000; it++) {
        vector<P> pa(rng() % 8 + 1), pb(rng() % 8 + 1);
        int w = rng() % 7 + 1;
        for (auto& q : pa) q = {(long long)(rng() % w) - 3, (long long)(rng() % w)};
        for (auto& q : pb) q = {(long long)(rng() % w), (long long)(rng() % w) - 3};
        vector<P> a = convex_hull(pa), b = convex_hull(pb), all;
        for (auto& x : a)
            for (auto& y : b) all.push_back(x + y);
        assert(convex_hull(minkowski_sum(a, b)) == convex_hull(all));
        assert((int)minkowski_sum(a, b).size() <= (int)(a.size() + b.size()));
    }
    // 入力：凸多角形 A と B（反時計回り）。和の頂点を、最も下の頂点から反時計回りに出力する
    int n, m;
    cin >> n;
    vector<P> a(n);
    for (auto& q : a) cin >> q.x >> q.y;
    cin >> m;
    vector<P> b(m);
    for (auto& q : b) cin >> q.x >> q.y;
    for (auto& q : minkowski_sum(a, b)) cout << q.x << ' ' << q.y << '\n';
}
