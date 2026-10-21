#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    long long a, b;  // 0 ≤ a, b ≤ 10^18
    cin >> a >> b;
    // --8<-- [start:core]
    // mint x = a * b;       // NG：long long の積があふれてから mint に直る
    mint x = mint(a) * b;    // OK：左が mint なので b も mint に直ってから掛ける
    mint bad = 1 / 2;        // NG：int の割り算で 0 になってから mint に直る
    mint half = mint(1) / 2; // OK：mint の割り算（2 の逆元を掛ける）
    mint d = mint(a) - b;    // 負になっても 0 以上 998244353 未満に直る
    cout << x.val() << ' ' << bad.val() << ' ' << half.val() << ' ' << d.val() << '\n';
    // --8<-- [end:core]
    assert(bad.val() == 0);
    assert((half * 2).val() == 1);
    assert(((d + b) - a).val() == 0);
}
