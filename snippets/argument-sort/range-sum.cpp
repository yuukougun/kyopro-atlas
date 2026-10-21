// 点 i（原点ではない）に重み w[i] がある。各クエリで方向 u, v が与えられ、
// u から反時計回りに v まで回る間（u と v の方向を含む）にある点の重みの和を答える。
// u と v が同じ方向なら、その方向の点だけを数える。
#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};

long long cross(P a, P b) { return a.x * b.y - a.y * b.x; }

int half(P p) { return (p.y > 0 || (p.y == 0 && p.x > 0)) ? 0 : 1; }  // 原点は来ない

bool arg_less(P a, P b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    return cross(a, b) > 0;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<pair<P, long long>> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first.x >> pts[i].first.y >> pts[i].second;
        assert(pts[i].first.x != 0 || pts[i].first.y != 0);
    }
    // --8<-- [start:core]
    sort(pts.begin(), pts.end(), [](const auto& a, const auto& b) { return arg_less(a.first, b.first); });
    vector<P> d(n);
    vector<long long> s(n + 1, 0);  // s[i]：並べた後の先頭 i 個の重みの和
    for (int i = 0; i < n; i++) {
        d[i] = pts[i].first;
        s[i + 1] = s[i] + pts[i].second;
    }
    for (int k = 0; k < q; k++) {
        P u, v;
        cin >> u.x >> u.y >> v.x >> v.y;
        // l：偏角が u 以上の最初の位置、r：偏角が v より大きい最初の位置（同じ方向の点は比較で等しい）
        int l = lower_bound(d.begin(), d.end(), u, arg_less) - d.begin();
        int r = upper_bound(d.begin(), d.end(), v, arg_less) - d.begin();
        long long ans;
        if (!arg_less(v, u)) ans = s[r] - s[l];  // u ≤ v：[l, r) をそのまま
        else ans = (s[n] - s[l]) + s[r];          // 一周をまたぐ：[l, n) と [0, r)
        cout << ans << '\n';
    }
    // --8<-- [end:core]
}
