// 実数の二分探索：c ≥ 0 に対して f(t) = t^3 + t = c となる t ≥ 0 を求める。
// 反復回数を固定し、「f(lo) ≤ c < f(hi)」を保ったまま区間を半分にし続ける。
#include <bits/stdc++.h>
using namespace std;

int main() {
    double c;
    cin >> c;
    assert(c >= 0);
    auto f = [](double t) { return t * t * t + t; };

    // --8<-- [start:core]
    double lo = 0.0;      // f(0) = 0 ≤ c
    double hi = c + 1.0;  // f(c + 1) > c
    for (int iter = 0; iter < 100; iter++) {  // 幅は 2^100 分の 1 になり、double の精度の限界まで縮む
        double mid = (lo + hi) / 2;
        if (f(mid) <= c) lo = mid;
        else hi = mid;
    }
    cout << fixed << setprecision(9) << lo << '\n';  // 桁数の指定を忘れない
    // --8<-- [end:core]
}
