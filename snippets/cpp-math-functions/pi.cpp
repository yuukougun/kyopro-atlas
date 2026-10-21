#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    double p1 = numbers::pi;                         // C++20。<numbers> にある（bits/stdc++.h に含まれる）
    double p2 = M_PI;                                // POSIX のマクロ。規格の外だが GCC では使える
    double p3 = acos(-1.0);                          // 昔からの書き方
    long double pl = numbers::pi_v<long double>;     // long double の精度の円周率
    // --8<-- [end:core]
    assert(p1 == p2 && p2 == p3);
    cout << fixed << setprecision(18) << p1 << '\n' << pl << '\n';
}
