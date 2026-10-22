#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
int main() {
    // --8<-- [start:core]
    using mint = atcoder::modint998244353;
    // v1.6 なら int、v1.5 以前なら unsigned int で、v1.5 以前はここでコンパイルエラーになる
    static_assert(is_same_v<decltype(mint(1).val()), int>);
    mint a = 1, b = 2;
    cout << a.val() - b.val() << '\n';  // v1.6 では -1（v1.5 では 4294967295）
    // --8<-- [end:core]
}
