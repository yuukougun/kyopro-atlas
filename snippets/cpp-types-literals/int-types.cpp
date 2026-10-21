#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    cout << numeric_limits<int>::max() << '\n';                 // 2147483647（約 2.1×10^9）
    cout << numeric_limits<unsigned>::max() << '\n';            // 4294967295（約 4.3×10^9）
    cout << numeric_limits<long long>::max() << '\n';           // 9223372036854775807（約 9.2×10^18）
    cout << numeric_limits<unsigned long long>::max() << '\n';  // 18446744073709551615（約 1.8×10^19）
    // 64 bit の Linux（AtCoder・手元）での正体
    static_assert(is_same_v<size_t, unsigned long>);  // unsigned long long とは別の型
    static_assert(is_same_v<int64_t, long>);          // long long とは別の型
    static_assert(sizeof(long) == 8 && sizeof(long long) == 8);
    // --8<-- [end:core]
}
