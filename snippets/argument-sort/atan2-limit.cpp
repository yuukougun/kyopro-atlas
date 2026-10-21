// 座標が 10^9 規模の 2 つの方向は、atan2 の値（double）では区別できないが、外積なら区別できる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long ax = 1000000000, ay = 999999999;  // a = (10^9, 10^9 - 1)
    long long bx = 999999999, by = 999999998;   // b = (10^9 - 1, 10^9 - 2)
    double ta = atan2((double)ay, (double)ax), tb = atan2((double)by, (double)bx);
    cout << (ta == tb ? "same" : "different") << '\n';  // same：double では同じ角度になる
    cout << ax * by - ay * bx << '\n';                  // -1：b は a の右側（時計回りの側）にある
    // --8<-- [end:core]
}
