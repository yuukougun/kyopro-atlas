// 法 m が素数とは限らないとき、S(n) = 1 + r + … + r^(n−1) を mod m で求める。
// (S(n), r^n) の組を返す再帰で、n が偶数なら半分に、奇数なら 1 つ減らす。m ≤ 10^9 を想定。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 返り値は {S(n) mod m, r^n mod m}
pair<long long, long long> geo_sum(long long r, long long n, long long m) {
    if (n == 0) return {0, 1 % m};                  // S(0) = 0、r^0 = 1（m = 1 なら 0）
    if (n % 2 == 1) {                               // S(n) = 1 + r·S(n−1)
        auto [s, p] = geo_sum(r, n - 1, m);
        return {(1 + r % m * s) % m, r % m * p % m};
    }
    auto [s, p] = geo_sum(r, n / 2, m);             // k = n/2：S(2k) = S(k)·(1 + r^k)
    return {s * ((1 + p) % m) % m, p * p % m};      // 積は 10^18 未満に収まる
}
// --8<-- [end:core]

int main() {
    // 素朴な和と比べる（逆元のない法・m = 1 を含める）
    for (long long m : {1LL, 2LL, 6LL, 10LL, 12LL, 998244353LL, 1000000000LL}) {
        for (long long r : {0LL, 1LL, 2LL, 3LL, 7LL, 10LL, 999999999LL}) {
            long long s = 0, t = 1 % m;
            for (long long n = 0; n <= 40; n++) {
                auto [gs, gp] = geo_sum(r, n, m);
                assert(gs == s && gp == t);
                s = (s + t) % m;
                t = t * (r % m) % m;
            }
        }
    }
    long long r, n, m;
    cin >> r >> n >> m;
    cout << geo_sum(r, n, m).first << '\n';
}
