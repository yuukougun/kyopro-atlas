// n が巨大（10^18 まで）で k が小さいとき、C(n, k) = n(n-1)…(n-k+1) / k! を O(k + log p) で求める。
// k < p なら k! は p で割り切れないので、n ≥ p でも正しい。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint binom_large(long long n, int k) {
    if (k < 0 || k > n) return 0;
    mint num = 1, den = 1;
    for (int i = 0; i < k; i++) {
        num *= mint(n - i);  // 分子：n から k 個（mint は long long から mod を取って作る）
        den *= i + 1;        // 分母：k!
    }
    return num * den.inv();  // 逆元は最後に 1 回だけ
}
// --8<-- [end:core]

int main() {
    long long n;
    int k;
    cin >> n >> k;
    cout << binom_large(n, k).val() << '\n';
}
