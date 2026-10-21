#include <bits/stdc++.h>
using namespace std;

int main() {
    __int128 a = -6, b = 4;
    // --8<-- [start:core]
    // -std=gnu++23（AtCoder）なら通る
    long long g = (long long)gcd(a, b);  // static assertion failed: std::gcd arguments must be integers
    long long h = (long long)abs(a);     // call of overloaded 'abs(__int128&)' is ambiguous
    // --8<-- [end:core]
    cout << g << ' ' << h << '\n';
}
