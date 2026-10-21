#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int64_t a = 1;
    long long b = 2;
    cout << max(a, b) << '\n';  // コンパイルエラー：long と long long は別の型
    // --8<-- [end:core]
}
