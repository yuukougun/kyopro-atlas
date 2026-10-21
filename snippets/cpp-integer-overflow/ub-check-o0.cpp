#include <bits/stdc++.h>
using namespace std;

// ub-check.cpp を -O0 で確かめる（本文には取り込まない）
int main() {
    int a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    int c = a * b;                  // あふれうる（未定義動作）
    long long p = (long long)a * b; // 正しい積
    cout << c << ' ' << p << ' ' << (c == p ? "same" : "differ") << '\n';
    // -O2：1410065408 10000000000 same   ← 違う 2 つの値を「同じ」と判定する
    // -O0：1410065408 10000000000 differ
    // --8<-- [end:core]
}
