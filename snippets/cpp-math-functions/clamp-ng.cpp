#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x = 5, n = 3;
    // --8<-- [start:core]
    cout << clamp(x, 0, n) << '\n';    // コンパイルエラー：x と n は long long、0 は int
    cout << clamp(x, 0LL, n) << '\n';  // 3 つの型をそろえれば通る
    // --8<-- [end:core]
}
