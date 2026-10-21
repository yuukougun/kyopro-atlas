#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<mint> fact(n + 1);  // mint の vector は 0 で埋まる
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;  // 掛けるたびに 998244353 で割った余りになる
    mint x = mint(-1);         // 負の数は 998244352 に直る
    mint half = mint(1) / 2;   // 割り算は逆元を掛ける（法が素数で、0 で割らないとき）
    cout << fact[n].val() << ' ' << x.val() << ' ' << (half * 2).val() << '\n';
    // --8<-- [end:core]
}
