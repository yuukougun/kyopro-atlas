#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

const int MAX = 400000;  // 二項係数の上側の最大（n + k − 1 まで要る）
vector<mint> fact(MAX + 1), ifact(MAX + 1);

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) fact[i] = fact[i - 1] * i;
    ifact[MAX] = fact[MAX].inv();
    for (int i = MAX; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

// --8<-- [start:core]
// C(n, r)。範囲外（r < 0・r > n・n < 0）は 0
mint comb(long long n, long long r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return fact[n] * ifact[r] * ifact[n - r];
}

// x_1 + … + x_k = n の非負整数解の数
mint count_nonneg(long long n, long long k) {
    if (k == 0) return n == 0 ? 1 : 0;  // 式の C(n − 1, −1) では n = 0 を数え損なう
    return comb(n + k - 1, k - 1);
}

// x_1 + … + x_k = n の正の整数解の数
mint count_pos(long long n, long long k) {
    if (k == 0) return n == 0 ? 1 : 0;
    return comb(n - 1, k - 1);  // n < k なら自動的に 0
}

// x_1 + … + x_k ≤ n の非負整数解の数（余りの変数を 1 つ足す）
mint count_nonneg_at_most(long long n, long long k) {
    return count_nonneg(n, k + 1);
}
// --8<-- [end:core]

// 小さい n・k で全探索と比べる
long long brute(int n, int k, int lo, bool at_most) {
    long long cnt = 0;
    auto dfs = [&](auto&& self, int i, int rest) -> void {
        if (i == k) {
            if (rest == 0 || (at_most && rest > 0)) cnt++;
            return;
        }
        for (int v = lo; v <= rest; v++) self(self, i + 1, rest - v);
    };
    dfs(dfs, 0, n);
    return cnt;
}

int main() {
    init();
    for (int n = 0; n <= 8; n++) {
        for (int k = 0; k <= 5; k++) {
            assert(count_nonneg(n, k).val() == brute(n, k, 0, false));
            assert(count_pos(n, k).val() == brute(n, k, 1, false));
            assert(count_nonneg_at_most(n, k).val() == brute(n, k, 0, true));
        }
    }
    long long n, k;
    cin >> n >> k;
    cout << count_nonneg(n, k).val() << ' ' << count_pos(n, k).val() << ' '
         << count_nonneg_at_most(n, k).val() << '\n';
}
