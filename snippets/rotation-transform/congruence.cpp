// 点集合の合同判定（回転と平行移動。反転は許さない）を整数だけで行う
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
using P = pair<long long, long long>;

// 重心を原点に移す。割り算を避けるため、座標を N 倍してから重心（の N 倍）を引く
vector<P> centralize(const vector<P>& a) {
    long long n = a.size(), sx = 0, sy = 0;
    for (auto [x, y] : a) sx += x, sy += y;
    vector<P> r;
    for (auto [x, y] : a) r.push_back({n * x - sx, n * y - sy});
    return r;
}

bool congruent(const vector<P>& s0, const vector<P>& t0) {
    vector<P> s = centralize(s0), t = centralize(t0);
    int n = s.size();
    vector<P> sorted_t = t;
    sort(sorted_t.begin(), sorted_t.end());
    int base = -1;  // 原点（重心）にない S の点を 1 つ選ぶ
    for (int i = 0; i < n; i++)
        if (s[i] != P{0, 0}) base = i;
    if (base == -1) return s == t;  // 全点が重心にある（N = 1）
    auto [ax, ay] = s[base];
    long long r2 = ax * ax + ay * ay;
    for (auto [bx, by] : t) {
        if (bx * bx + by * by != r2) continue;  // 長さが違えば回転で重ならない
        // a を b に重ねる回転は、cos = d / r2、sin = c / r2（d は内積、c は外積）
        long long d = ax * bx + ay * by, c = ax * by - ay * bx;
        // 回した点を r2 倍した整数で比べる（割り算をしない）
        vector<P> rot;
        for (auto [x, y] : s) rot.push_back({d * x - c * y, c * x + d * y});
        vector<P> scaled = sorted_t;
        for (auto& [x, y] : scaled) x *= r2, y *= r2;
        sort(rot.begin(), rot.end());
        if (rot == scaled) return true;
    }
    return false;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<P> s(n), t(n);
    for (auto& [x, y] : s) cin >> x >> y;
    for (auto& [x, y] : t) cin >> x >> y;
    cout << (congruent(s, t) ? "Yes" : "No") << '\n';
}
