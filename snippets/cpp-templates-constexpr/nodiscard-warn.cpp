#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
[[nodiscard]] long long gcd_ll(long long a, long long b) {
    return b == 0 ? a : gcd_ll(b, a % b);
}

int main() {
    long long g = 12;
    gcd_ll(g, 18);  // 警告：戻り値を捨てている（g = gcd_ll(g, 18) の書き忘れ）
    cout << g << '\n';
}
// --8<-- [end:core]
