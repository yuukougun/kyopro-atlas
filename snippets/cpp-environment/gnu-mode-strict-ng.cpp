#include <bits/stdc++.h>
using namespace std;
int main() {
    // --8<-- [start:core]
    int x = 3;
    typeof(x) y = x;                         // GNU 拡張の typeof
    static_assert(is_integral_v<__int128>);  // gnu++23 では true
    __int128 a = -6, b = 4;
    cout << y << ' ' << (long long)gcd(a, b) << ' ' << (long long)abs(a) << '\n';
    // --8<-- [end:core]
}
