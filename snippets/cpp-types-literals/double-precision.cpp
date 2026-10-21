#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    cout << numeric_limits<double>::digits << '\n';       // 53（仮数部のビット数）
    cout << numeric_limits<long double>::digits << '\n';  // 64（x86-64 の GCC）
    long long p = 1LL << 53;                              // 9007199254740992
    cout << (long long)(double)(p + 1) << '\n';           // 9007199254740992（+1 が消える）
    cout << (long long)(long double)(p + 1) << '\n';      // 9007199254740993（long double なら残る）
    // --8<-- [end:core]
}
