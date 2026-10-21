#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    cout << __gcd(12, 18LL) << '\n';  // コンパイルエラー：__gcd は 2 つの引数が同じ型でないと通らない
    // --8<-- [end:core]
}
