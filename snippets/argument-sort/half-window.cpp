// 各点 i（原点ではない）について、i の方向から反時計回りに 0 より大きく π より小さい角度の範囲
// （i から見て左側の開いた半平面）にある点の数を、入力の順に出力する。
// 同じ方向の点をまとめた方向の列を 2 周分に見て、尺取りで求める。
#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
};

long long cross(P a, P b) { return a.x * b.y - a.y * b.x; }

int half(P p) { return (p.y > 0 || (p.y == 0 && p.x > 0)) ? 0 : 1; }

bool arg_less(P a, P b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    return cross(a, b) > 0;
}

int main() {
    int n;
    cin >> n;
    vector<P> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        assert(p[i].x != 0 || p[i].y != 0);
    }
    // --8<-- [start:core]
    vector<P> sorted_p = p;
    sort(sorted_p.begin(), sorted_p.end(), arg_less);
    vector<P> d;          // 異なる方向を偏角の順に
    vector<long long> c;  // c[j]：方向 d[j] の点の数
    for (int i = 0; i < n; i++) {
        if (!d.empty() && !arg_less(d.back(), sorted_p[i])) c.back()++;  // 直前と同じ方向
        else d.push_back(sorted_p[i]), c.push_back(1);
    }
    int m = d.size();
    vector<long long> s(2 * m + 1, 0);  // 2 周分の個数の累積和
    for (int j = 0; j < 2 * m; j++) s[j + 1] = s[j] + c[j % m];
    vector<long long> left_cnt(m);  // left_cnt[i]：d[i] から見て左側の開いた半平面にある点の数
    int e = 0;                      // 2 周分の添字で、d[i] の左側に入らない最初の位置
    for (int i = 0; i < m; i++) {
        e = max(e, i + 1);
        while (e < i + m && cross(d[i], d[e % m]) > 0) e++;  // i が進んでも e は戻らない
        left_cnt[i] = s[e] - s[i + 1];
    }
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) {
        int j = lower_bound(d.begin(), d.end(), p[i], arg_less) - d.begin();
        cout << left_cnt[j] << '\n';
    }
}
