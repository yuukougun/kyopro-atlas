#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    static_assert(is_same_v<decltype(1LL), long long>);
    static_assert(is_same_v<decltype(1ULL), unsigned long long>);
    static_assert(is_same_v<decltype(0uz), size_t>);   // C++23
    static_assert(is_same_v<decltype(3000000000), long>);  // int に収まらない数は自動で広がる
    static_assert(is_same_v<decltype(1e9), double>);   // 指数表記は整数でも double
    static_assert(1'000'000'007 == 1000000007);        // 桁区切り（C++14）
    static_assert(0b1010 == 10);                       // 2 進（C++14）
    static_assert(0x3f3f3f3f == 1061109567);           // 16 進
    // --8<-- [end:core]
    constexpr long long MOD = 998'244'353;
    long long x;
    cin >> x;
    cout << x % MOD << '\n';
}
