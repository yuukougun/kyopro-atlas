#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    vector<mint> v = {3, 1, mint(-1)};
    // --8<-- [start:core]
    ranges::sort(v, {}, [](mint x) { return x.val(); });  // val() の値で並べる（元の整数の大小ではない）
    // --8<-- [end:core]
    for (mint x : v) cout << x.val() << ' ';
    cout << '\n';
}
