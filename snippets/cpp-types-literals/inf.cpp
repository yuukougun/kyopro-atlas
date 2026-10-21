#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    constexpr int INF32 = 0x3f3f3f3f;       // 1061109567
    constexpr long long INF64 = 1LL << 60;  // 1152921504606846976
    static_assert(INF32 + INF32 <= numeric_limits<int>::max());        // 2 倍しても int に収まる
    static_assert(INF64 + INF64 <= numeric_limits<long long>::max());  // 2 倍しても収まる
    int d[5];
    memset(d, 0x3f, sizeof d);  // 各バイトを 0x3f にすると、各要素が 0x3f3f3f3f になる
    cout << (d[4] == INF32) << '\n';
    // --8<-- [end:core]
    long long x;
    cin >> x;
    cout << min(INF64, x) << '\n';
}
