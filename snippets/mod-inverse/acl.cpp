// ACL の inv_mod と modint の inv・割り算。入力：a b。
// 出力：inv_mod(a, 10) を gcd(a, 10) == 1 のときだけ、続いて a / b mod 998244353。
#include <bits/stdc++.h>
#include <atcoder/math>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    long long a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    // 一般の法：gcd(a, m) == 1 を確かめてから呼ぶ（でないと assert で止まる）
    if (gcd(a, 10LL) == 1) cout << atcoder::inv_mod(a, 10) << '\n';

    // 素数の法の modint：割り算は b の逆元を掛ける。b ≡ 0 (mod p) は不可
    assert(b % mint::mod() != 0);
    mint q = mint(a) / mint(b);       // = mint(a) * mint(b).inv()
    cout << q.val() << '\n';
    // --8<-- [end:core]
}
