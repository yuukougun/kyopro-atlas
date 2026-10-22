#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};
bool operator<(P a, P b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }
bool operator==(P a, P b) { return a.x == b.x && a.y == b.y; }
// o から見た a・b の外積（反時計回りが正）
long long cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }
long long dist2(P a, P b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Andrew 法。反時計回りで、一直線上の点を除いた凸包の頂点を返す
vector<P> convex_hull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n <= 1) return p;
    vector<P> h(2 * n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k - 1);
    return h;
}

// --8<-- [start:core]
// h：凸包の頂点（反時計回り、一直線上の点を除く）。最遠点対の距離の 2 乗を返す
long long furthest_pair(const vector<P>& h) {
    int n = h.size();
    if (n == 1) return 0;
    if (n == 2) return dist2(h[0], h[1]);
    long long best = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int i2 = (i + 1) % n;
        // 辺 (i, i2) から最も遠い頂点まで j を進める（三角形の面積の 2 倍で比べる）
        while (cross(h[i], h[i2], h[(j + 1) % n]) > cross(h[i], h[i2], h[j])) j = (j + 1) % n;
        best = max({best, dist2(h[i], h[j]), dist2(h[i2], h[j])});
    }
    return best;
}
// --8<-- [end:core]

long long brute(const vector<P>& p) {
    long long best = 0;
    for (auto& a : p)
        for (auto& b : p) best = max(best, dist2(a, b));
    return best;
}

int main() {
    // 小さい乱数の入力で、全組の比較と照らし合わせる
    mt19937 rng(12345);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 12 + 1;
        int w = rng() % 6 + 1;
        vector<P> p(n);
        for (auto& q : p) q = {(long long)(rng() % w), (long long)(rng() % w)};
        assert(furthest_pair(convex_hull(p)) == brute(p));
    }
    int n;
    cin >> n;
    vector<P> p(n);
    for (auto& q : p) cin >> q.x >> q.y;
    cout << furthest_pair(convex_hull(p)) << '\n';
}
