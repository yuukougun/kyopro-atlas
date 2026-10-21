#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
[[nodiscard]] long long gcd_ll(long long a, long long b) {  // 戻り値を捨てると警告
    return b == 0 ? a : gcd_ll(b, a % b);
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);  // 入力の値は 0 以上とする
    for (auto& x : a) cin >> x;
    // --8<-- [start:body]
    [[maybe_unused]] int unused_debug = 0;  // 使わなくても -Wunused-variable が出ない
    long long g = 0;
    for (long long x : a) {
        g = gcd_ll(g, x);
        if (g == 1) [[unlikely]] break;  // 分岐の起きやすさの目安（C++20）
    }
    // 入力が 0 以上なので g >= 0 が成り立つ。負の値が来ると前提が崩れ、未定義動作になる
    [[assume(g >= 0)]];  // g >= 0 と仮定して最適化してよい（C++23・GCC 13〜）
    // --8<-- [end:body]
    cout << g << '\n';
}
