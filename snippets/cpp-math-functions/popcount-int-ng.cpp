#include <bits/stdc++.h>
using namespace std;

int main() {
    int s = 5;
    // --8<-- [start:core]
    cout << popcount(s) << '\n';  // コンパイルエラー：std::popcount は符号なし整数しか受けない
    // --8<-- [end:core]
}
