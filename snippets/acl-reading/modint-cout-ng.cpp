#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    mint x = 3;
    // --8<-- [start:core]
    cout << x << '\n';  // コンパイルエラー：mint は << で出せない
    // --8<-- [end:core]
}
