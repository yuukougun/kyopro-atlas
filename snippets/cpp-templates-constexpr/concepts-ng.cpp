#include <bits/stdc++.h>
using namespace std;

template <integral T>
T floor_div(T a, T b) {
    return a / b - (a % b != 0 && a < 0);
}

int main() {
    // --8<-- [start:core]
    cout << floor_div(7.0, 2.0) << '\n';  // コンパイルエラー：double は integral を満たさない
    // --8<-- [end:core]
}
