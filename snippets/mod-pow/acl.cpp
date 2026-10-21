#include <bits/stdc++.h>
#include <atcoder/math>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    long long x, n;
    int m;
    cin >> x >> n >> m;
    // --8<-- [start:core]
    long long r1 = atcoder::pow_mod(x, n, m);  // x^n mod m（m は int、x は負でもよい）
    mint r2 = mint(x).pow(n);                  // 998244353 を法とする x^n
    // --8<-- [end:core]
    cout << r1 << ' ' << r2.val() << '\n';
}
