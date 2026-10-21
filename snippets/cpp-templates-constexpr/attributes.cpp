#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
[[nodiscard]] long long gcd_ll(long long a, long long b) {  // 戻り値を捨てると警告
    return b == 0 ? a : gcd_ll(b, a % b);
}

int main() {
    [[maybe_unused]] int unused_debug = 0;  // 使わなくても -Wunused-variable が出ない
    int n;
    cin >> n;
    long long g = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        g = gcd_ll(g, a);
        if (g == 1) [[unlikely]] break;  // 分岐の起きやすさの目安（C++20）
    }
    [[assume(g >= 0)]];  // g >= 0 と仮定して最適化してよい（C++23・GCC 13〜）
    cout << g << '\n';
}
// --8<-- [end:core]
