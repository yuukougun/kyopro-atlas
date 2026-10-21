#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    // -std=c++23 でも -std=gnu++23 でも使える
    __int128 mx = numeric_limits<__int128>::max();  // 2^127 - 1
    cout << (long long)(mx >> 64) << '\n';          // 9223372036854775807
    cout << is_integral_v<__int128> << '\n';        // -std=c++23 では 0、-std=gnu++23 では 1
    // --8<-- [end:core]
}
