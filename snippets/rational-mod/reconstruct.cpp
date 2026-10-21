// 検算用：mod 998244353 の値 r を、分子・分母の小さい分数 a/q に戻す（有理数復元）。
// 分母 q を 1 から順に試し、r × q mod p が小さい（または p から引くと小さい）ものを探す。
// |a| ≤ B かつ 1 ≤ q ≤ B で 2B² < p なら、見つかる分数はただ 1 つである。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long MOD = 998244353;
const long long B = 22341;  // 2 × 22341² < 998244353

// 見つかれば {a, q}（r ≡ a × q^(−1)）、見つからなければ {0, 0}
pair<long long, long long> reconstruct(long long r) {
    for (long long q = 1; q <= B; q++) {
        long long a = r * q % MOD;               // a ≡ r × q
        if (a <= B) return {a, q};               // 正の分数 a/q
        if (MOD - a <= B) return {a - MOD, q};   // 負の分数 −(MOD − a)/q
    }
    return {0, 0};
}
// --8<-- [end:core]

int main() {
    long long r;
    cin >> r;
    auto [a, q] = reconstruct(r);
    if (q == 0) {
        cout << "not found" << '\n';
    } else {
        cout << a << "/" << q << '\n';
    }
    assert(reconstruct(499122177) == make_pair(1LL, 2LL));  // 1/2
}
