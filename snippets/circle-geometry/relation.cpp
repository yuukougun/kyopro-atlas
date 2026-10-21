#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 2 円の位置関係を整数だけで判定する。
// 0：離れる、1：外接、2：交わる（共有点 2 つ）、3：内接、4：内包、5：一致
// 座標と半径の絶対値が 10^9 以下なら、どの 2 乗も long long に収まる
int circle_relation(long long x1, long long y1, long long r1,
                    long long x2, long long y2, long long r2) {
    long long dx = x1 - x2, dy = y1 - y2;
    long long d2 = dx * dx + dy * dy;       // 中心間の距離の 2 乗
    long long s2 = (r1 + r2) * (r1 + r2);   // 半径の和の 2 乗
    long long t2 = (r1 - r2) * (r1 - r2);   // 半径の差の 2 乗
    if (d2 == 0 && r1 == r2) return 5;     // 中心も半径も同じなら一致（半径 0 の同じ点も）
    if (d2 > s2) return 0;
    if (d2 == s2) return 1;
    if (d2 > t2) return 2;
    if (d2 == t2) return 3;
    return 4;
}

// 共有点を持つか（外接・交わる・内接・一致）。t2 <= d2 <= s2 と同じ
bool touches(long long x1, long long y1, long long r1,
             long long x2, long long y2, long long r2) {
    int k = circle_relation(x1, y1, r1, x2, y2, r2);
    return k != 0 && k != 4;
}
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const string name[] = {"separate", "external", "intersect", "internal", "contain", "same"};
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        int k = circle_relation(x1, y1, r1, x2, y2, r2);
        assert(circle_relation(x2, y2, r2, x1, y1, r1) == k);  // 入れ替えても同じ
        cout << name[k] << ' ' << (touches(x1, y1, r1, x2, y2, r2) ? 1 : 0) << '\n';
    }
}
