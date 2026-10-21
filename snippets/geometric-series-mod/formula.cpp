// 素数 mod p = 998244353 で S(n) = 1 + r + … + r^(n−1) を公式 (r^n − 1)/(r − 1) で求める。
// r ≡ 1 (mod p) のときは分母が 0 になるので、和は n 個の 1 で n mod p。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint geo_sum(long long r, long long n) {  // r ≥ 0、n ≥ 0
    mint x = r;                            // r は mod p に直してから比べる
    if (x == 1) return mint(n);            // r ≡ 1：1 が n 個（n も mod p に直る）
    return (x.pow(n) - 1) / (x - 1);       // 逆元は x − 1 ≢ 0 なので存在する
}
// --8<-- [end:core]

int main() {
    // 素朴な和と比べる（r ≡ 1 になる r = p + 1 も含める）
    const long long p = 998244353;
    for (long long r : {0LL, 1LL, 2LL, 10LL, p - 1, p, p + 1}) {
        mint s = 0, t = 1;
        for (int n = 0; n <= 20; n++) {
            assert(geo_sum(r, n) == s);
            s += t;
            t *= r;
        }
    }
    long long r, n;
    cin >> r >> n;
    cout << geo_sum(r, n).val() << '\n';
}
