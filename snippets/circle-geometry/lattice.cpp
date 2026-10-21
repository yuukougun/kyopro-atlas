#include <bits/stdc++.h>
using namespace std;

const long long S = 10000;  // 小数第 4 位まで → 10^4 倍して整数にする

// 文字列 "-12.5" などを S 倍した整数にする（符号は最後に付ける）
long long parse_scaled(const string& s) {
    int i = 0;
    bool neg = false;
    if (s[i] == '-') neg = true, i++;
    long long ip = 0, fp = 0;
    int digits = 0;
    while (i < (int)s.size() && s[i] != '.') ip = ip * 10 + (s[i++] - '0');
    if (i < (int)s.size()) i++;  // '.'
    while (i < (int)s.size()) fp = fp * 10 + (s[i++] - '0'), digits++;
    while (digits < 4) fp *= 10, digits++;
    long long v = ip * S + fp;
    return neg ? -v : v;
}

// --8<-- [start:core]
long long floor_div(long long a, long long b) {  // b > 0
    return a >= 0 ? a / b : -((-a + b - 1) / b);
}
long long ceil_div(long long a, long long b) {   // b > 0
    return -floor_div(-a, b);
}
// r * r <= n となる最大の r（n >= 0）。sqrtl の見当を前後で補正する
long long isqrt(long long n) {
    long long r = sqrtl((long double)n);
    while (r > 0 && r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

// S 倍した座標で、中心 (cx, cy)・半径 r の円の内部と周上にある格子点
// （元の座標が整数の点＝ S 倍した座標が S の倍数の点）の数
long long lattice_points(long long cx, long long cy, long long r) {
    long long cnt = 0;
    for (long long k = ceil_div(cy - r, S); k <= floor_div(cy + r, S); k++) {
        long long dy = k * S - cy;
        long long w = isqrt(r * r - dy * dy);  // この行の x は [cx - w, cx + w]
        cnt += floor_div(cx + w, S) - ceil_div(cx - w, S) + 1;
    }
    return cnt;
}
// --8<-- [end:core]

int main() {
    string xs, ys, rs;
    cin >> xs >> ys >> rs;
    cout << lattice_points(parse_scaled(xs), parse_scaled(ys), parse_scaled(rs)) << '\n';
}
