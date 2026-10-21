#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long a = 5;
    int b = 7;
    cout << max(a, b) << '\n';  // コンパイルエラー：max は 2 つの引数が同じ型 T
    // --8<-- [end:core]
}
