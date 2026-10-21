#include <bits/stdc++.h>
#include <stdfloat>
using namespace std;

int main() {
    // --8<-- [start:core]
    float128_t x = 1.0f128 / 3;
    cout << x << '\n';  // コンパイルエラー：ambiguous overload for 'operator<<'
    // --8<-- [end:core]
}
