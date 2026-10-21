#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint;  // dynamic_modint<-1>。法は実行時に決める

int main() {
    // --8<-- [start:core]
    int m, n;
    cin >> m >> n;
    mint::set_mod(m);  // mint の値を作る前に呼ぶ（呼ばないと法は 998244353 のまま）
    mint prod = 1;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        prod *= x;  // x は m で割った余りに直ってから掛けられる
    }
    cout << prod.val() << '\n';
    // --8<-- [end:core]
    assert(mint::mod() == m);
    assert(0 <= prod.val() && prod.val() < m);
}
