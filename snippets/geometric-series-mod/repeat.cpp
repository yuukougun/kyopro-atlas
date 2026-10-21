// 正の整数 N（d 桁）を N 回並べた整数を 998244353 で割った余り。
// 値は N × (1 + 10^d + 10^(2d) + … + 10^((N−1)d)) なので、公比 10^d の等比数列の和になる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    long long n;
    cin >> n;
    // --8<-- [start:core]
    int d = to_string(n).size();             // N の桁数
    mint r = mint(10).pow(d);                // 公比 10^d（d ≤ 19 では r ≢ 1）
    mint sum = (r.pow(n) - 1) / (r - 1);     // 項数は N（指数の n は mod しない）
    mint ans = mint(n) * sum;                // N 自体も mod p に直してから掛ける
    // --8<-- [end:core]
    assert(r != 1);
    cout << ans.val() << '\n';
}
