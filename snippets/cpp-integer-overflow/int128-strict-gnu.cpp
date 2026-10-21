#include <bits/stdc++.h>
using namespace std;

int main() {
    __int128 a = -6, b = 4;
    // --8<-- [start:core]
    // -std=gnu++23（AtCoder）なら通る
    long long g = (long long)gcd(a, b);  // 2
    long long h = (long long)abs(a);     // 6
    // --8<-- [end:core]
    cout << g << ' ' << h << '\n';
}
