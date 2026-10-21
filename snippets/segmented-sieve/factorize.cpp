// 区間篩による素因数分解：閉区間 [lo, hi] の各数を、√hi 以下の素数で割って分解する。
// 入力 L R に対し、各 x について「x の正の約数の個数」を 1 行ずつ出力する。
#include <bits/stdc++.h>
using namespace std;

vector<long long> primes_up_to(long long s) {
    vector<char> small(s + 1, true);
    vector<long long> primes;
    for (long long p = 2; p <= s; p++) {
        if (!small[p]) continue;
        primes.push_back(p);
        for (long long q = p * p; q <= s; q += p) small[q] = false;
    }
    return primes;
}

int main() {
    long long lo, hi;
    cin >> lo >> hi;
    assert(1 <= lo && lo <= hi);
    long long s = 1;
    while ((s + 1) * (s + 1) <= hi) s++;  // s = ⌊√hi⌋
    vector<long long> primes = primes_up_to(s);
    int n = hi - lo + 1;

    // --8<-- [start:core]
    // rem[i]：x = lo + i のうち、まだ割っていない部分。f[i]：x の (素因数, 指数) の列
    vector<long long> rem(n);
    vector<vector<pair<long long, int>>> f(n);
    for (int i = 0; i < n; i++) rem[i] = lo + i;
    for (long long p : primes) {
        // 素因数分解では p 自身も p¹ と分解するので、p² からではなく ⌈lo/p⌉·p から
        for (long long x = (lo + p - 1) / p * p; x <= hi; x += p) {
            int e = 0;
            while (rem[x - lo] % p == 0) {  // 割れるだけ割る
                rem[x - lo] /= p;
                e++;
            }
            f[x - lo].push_back({p, e});
        }
    }
    for (int i = 0; i < n; i++) {
        if (rem[i] > 1) f[i].push_back({rem[i], 1});  // 残りは √hi より大きい素数 1 個
    }
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) {
        long long prod = 1, d = 1;
        for (auto [p, e] : f[i]) {
            for (int k = 0; k < e; k++) prod *= p;
            d *= e + 1;
        }
        assert(prod == lo + i);  // 分解を掛け戻すと元の数になる
        cout << d << '\n';
    }
}
