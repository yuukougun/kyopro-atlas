#include <bits/stdc++.h>
#include <stdfloat>
using namespace std;

int main() {
    // --8<-- [start:core]
    float128_t x = 1.0f128 / 3;                         // 接尾辞 f128
    cout << numeric_limits<float128_t>::digits << '\n';  // 113（仮数部のビット数）
    cout << format("{:.30f}", x) << '\n';               // cout << x はコンパイルエラー
    // --8<-- [end:core]
}
