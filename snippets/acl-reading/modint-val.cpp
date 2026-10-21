#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    // --8<-- [start:core]
    mint x = 0;
    static_assert(is_same_v<decltype(x.val()), int>);  // ACL v1.6 では int（v1.5 は unsigned int）
    cout << x.val() - 1 << '\n';                        // v1.6 は -1（v1.5 は 4294967295）
    cout << max(x.val(), 0) << '\n';                    // v1.6 は通る（v1.5 は型が合わずコンパイルエラー）
    println("{}", x.val());                             // val() なら println でも出せる
    // --8<-- [end:core]
}
