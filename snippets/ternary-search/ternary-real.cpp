// 実数の三分探索：c ≥ 0 に対して、x ≥ 0 での f(x) = x + c / (1 + x) の最小値を求める。
// f は下に凸（x と c / (1 + x) の和）。f(0) = c で、x > c では f(x) > x > c なので、最小は [0, c] にある。
#include <bits/stdc++.h>
using namespace std;

int main() {
    double c;
    cin >> c;
    assert(c >= 0);
    auto f = [&](double x) { return x + c / (1 + x); };

    // --8<-- [start:core]
    double l = 0.0, r = c;  // 最小を与える x は閉区間 [l, r] の中にある
    for (int iter = 0; iter < 100; iter++) {  // 幅は (2/3)^100 ≒ 2.5×10^−18 倍になる
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) r = m2;  // 最小は m2 より右にない
        else l = m1;                // 最小は m1 より左にない（凸なので等しいときもこちらでよい）
    }
    cout << fixed << setprecision(9) << f(l) << '\n';  // x ではなく f の値を出す
    // --8<-- [end:core]
}
