#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

bool touches(long long x1, long long y1, long long r1,
             long long x2, long long y2, long long r2) {
    long long dx = x1 - x2, dy = y1 - y2;
    long long d2 = dx * dx + dy * dy;
    return (r1 - r2) * (r1 - r2) <= d2 && d2 <= (r1 + r2) * (r1 + r2);
}

// --8<-- [start:core]
// 円周の上だけを動いて、点 s から点 t へ行けるか。
// s と t を半径 0 の円として足すと、「点が円周上にある」も同じ判定で済む
bool reachable(vector<array<long long, 3>> c,  // {x, y, r}
               long long sx, long long sy, long long tx, long long ty) {
    c.push_back({sx, sy, 0});
    c.push_back({tx, ty, 0});
    int m = c.size();
    atcoder::dsu d(m);
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            auto [x1, y1, r1] = c[i];
            auto [x2, y2, r2] = c[j];
            if (touches(x1, y1, r1, x2, y2, r2)) d.merge(i, j);
        }
    }
    return d.same(m - 2, m - 1);
}
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    vector<array<long long, 3>> c(n);
    for (auto& [x, y, r] : c) cin >> x >> y >> r;
    cout << (reachable(c, sx, sy, tx, ty) ? "Yes" : "No") << '\n';
}
