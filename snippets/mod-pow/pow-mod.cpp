#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a^n mod m を返す（0 ≤ n、1 ≤ m < 2^31）。0^0 は 1 とする
long long mod_pow(long long a, long long n, long long m) {
    a %= m;
    if (a < 0) a += m;      // 負の底を 0 以上に直す
    long long res = 1 % m;  // m = 1 なら答えは 0
    while (n > 0) {
        // 不変条件：res × a^n ≡ （求めたい値） (mod m)
        if (n & 1) res = res * a % m;  // 2 進表記の最下位が 1 なら今の a を掛ける
        a = a * a % m;                 // a^(2^k) → a^(2^(k+1))
        n >>= 1;
    }
    return res;
}
// --8<-- [end:core]

// --8<-- [start:recursive]
// 再帰版：a^n = (a^(n/2))^2 × (n が奇数なら a)。a は 0 ≤ a < m に直してから呼ぶ
long long mod_pow_rec(long long a, long long n, long long m) {
    if (n == 0) return 1 % m;
    long long half = mod_pow_rec(a, n / 2, m);
    long long res = half * half % m;
    if (n & 1) res = res * a % m;
    return res;
}
// --8<-- [end:recursive]

int main() {
    long long a, n, m;
    cin >> a >> n >> m;
    long long ans = mod_pow(a, n, m);
    long long a0 = ((a % m) + m) % m;
    assert(ans == mod_pow_rec(a0, n, m));
    if (n <= 1000) {  // 小さい n は 1 回ずつ掛けた結果と比べる
        long long r = 1 % m;
        for (long long i = 0; i < n; i++) r = r * a0 % m;
        assert(r == ans);
    }
    cout << ans << '\n';
}
