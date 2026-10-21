#include <bits/stdc++.h>
using namespace std;

int main() {
    __int128 a = -6, b = 4;
    // --8<-- [start:core]
    // -std=c++23 でだけコンパイルエラー（-std=gnu++23 なら 2 と 6）
    long long g = (long long)gcd(a, b);  // static assertion failed: std::gcd arguments must be integers
    long long h = (long long)abs(a);     // call of overloaded 'abs(__int128&)' is ambiguous
    // --8<-- [end:core]
    cout << g << ' ' << h << '\n';
}
