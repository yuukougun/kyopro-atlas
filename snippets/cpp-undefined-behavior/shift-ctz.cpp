#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    unsigned int x;
    cin >> k >> x;
    // --8<-- [start:core]
    unsigned int a = 1u << k;              // k >= 32 は未定義動作。x86-64 では k = 32 で 1 になった（0 ではない）
    long long b = 1LL << k;                // 64 bit の型なら k <= 62 まで正しい
    int c = (x == 0 ? 32 : countr_zero(x));  // __builtin_ctz(0) は未定義。countr_zero(0u) は 32 と決まっている
    cout << a << ' ' << b << ' ' << c << '\n';
    // --8<-- [end:core]
}
