// ルジャンドルの公式：n! に含まれる素数 p の指数 v_p(n!) = Σ_k ⌊n / p^k⌋ を求める。
// 入力 n p（0 ≤ n ≤ 10^18、p は 2 以上の素数）。p^k を作らず、n を p で割りながら足す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long legendre(long long n, long long p) {
    long long res = 0;
    while (n > 0) {
        n /= p;    // n = ⌊元の n / p^k⌋（p^k を作らないのであふれない）
        res += n;  // p^k の倍数の個数を足す
    }
    return res;
}
// --8<-- [end:core]

int main() {
    long long n, p;
    cin >> n >> p;
    assert(0 <= n && 2 <= p);
    cout << legendre(n, p) << '\n';
}
