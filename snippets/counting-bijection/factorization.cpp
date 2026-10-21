#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

const int MAX = 200000;  // N − 1 + e ≤ 10^5 + 30 程度まで要る
vector<mint> fact(MAX + 1), ifact(MAX + 1);

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) fact[i] = fact[i - 1] * i;
    ifact[MAX] = fact[MAX].inv();
    for (int i = MAX; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}
mint comb(long long n, long long r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return fact[n] * ifact[r] * ifact[n - r];
}

// --8<-- [start:core]
// 積が m になる長さ n の正の整数列の個数
mint count_product(long long n, long long m) {
    mint res = 1;
    for (long long p = 2; p * p <= m; p++) {
        if (m % p != 0) continue;
        long long e = 0;
        while (m % p == 0) m /= p, e++;
        // 素数 p の指数 e を n 個の項へ配る：x_1 + … + x_n = e の非負整数解
        res *= comb(e + n - 1, n - 1);
    }
    if (m > 1) res *= comb(1 + n - 1, n - 1);  // 残った素数は指数 1
    return res;
}
// --8<-- [end:core]

// 小さい n・m で全探索と比べる
long long brute(int n, int m) {
    long long cnt = 0;
    auto dfs = [&](auto&& self, int i, int rest) -> void {
        if (i == n) {
            if (rest == 1) cnt++;
            return;
        }
        for (int d = 1; d <= rest; d++)
            if (rest % d == 0) self(self, i + 1, rest / d);
    };
    dfs(dfs, 0, m);
    return cnt;
}

int main() {
    init();
    for (int n = 1; n <= 4; n++)
        for (int m = 1; m <= 60; m++) assert(count_product(n, m).val() == brute(n, m));
    long long n, m;
    cin >> n >> m;
    cout << count_product(n, m).val() << '\n';
}
