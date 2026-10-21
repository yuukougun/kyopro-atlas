// 整数座標の点を偏角の順（正の x 軸から反時計回り、[0, 2π)）に並べる。原点は先頭に置く。
// 偏角の等しい点どうしは入力の順のまま（stable_sort）。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct P {
    long long x, y;
};

long long cross(P a, P b) { return a.x * b.y - a.y * b.x; }

// 0：原点、1：偏角が [0, π)（y > 0、または y = 0 かつ x > 0）、2：偏角が [π, 2π)
int half(P p) {
    if (p.x == 0 && p.y == 0) return 0;
    if (p.y > 0 || (p.y == 0 && p.x > 0)) return 1;
    return 2;
}

// a の偏角が b の偏角より小さいなら true（狭義の弱順序。同じ方向どうしは false）
bool arg_less(P a, P b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    return cross(a, b) > 0;  // 同じ半平面の中では、b が a の左側（反時計回りの側）にあれば a が先
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<P> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        assert(llabs(p[i].x) <= 1000000000 && llabs(p[i].y) <= 1000000000);
    }
    stable_sort(p.begin(), p.end(), arg_less);
    for (int i = 0; i < n; i++) cout << p[i].x << ' ' << p[i].y << '\n';
}
