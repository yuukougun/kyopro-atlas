// 区間篩：閉区間 [lo, hi] の各数が素数かを、√hi 以下の素数だけで判定する。
// 入力 L R（1 ≤ L ≤ R ≤ 10^12、R − L ≤ 10^6 程度）に対し、区間の素数の個数を出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 閉区間 [lo, hi] の各数が素数かを返す。is_prime[x - lo] が x の結果
vector<char> segmented_sieve(long long lo, long long hi) {
    // 1. ⌊√hi⌋ 以下の素数を普通の篩で列挙する（浮動小数点の sqrt は使わない）
    long long s = 1;
    while ((s + 1) * (s + 1) <= hi) s++;
    vector<char> small(s + 1, true);
    vector<long long> primes;
    for (long long p = 2; p <= s; p++) {
        if (!small[p]) continue;
        primes.push_back(p);
        for (long long q = p * p; q <= s; q += p) small[q] = false;
    }
    // 2. 区間の中の p の倍数に印を付ける。p 自身は消さないよう p² 以上から
    vector<char> is_prime(hi - lo + 1, true);
    for (long long p : primes) {
        long long start = max(p * p, (lo + p - 1) / p * p);  // 区間で最初の p の倍数
        for (long long x = start; x <= hi; x += p) is_prime[x - lo] = false;
    }
    if (lo == 1) is_prime[0] = false;  // 1 は素数でない
    return is_prime;
}
// --8<-- [end:core]

bool naive_prime(long long x) {
    if (x < 2) return false;
    for (long long d = 2; d * d <= x; d++)
        if (x % d == 0) return false;
    return true;
}

int main() {
    // 小さい区間で、試し割りと一致することを確かめる
    for (long long lo = 1; lo <= 60; lo++) {
        for (long long hi = lo; hi <= lo + 40; hi++) {
            vector<char> r = segmented_sieve(lo, hi);
            for (long long x = lo; x <= hi; x++) assert(r[x - lo] == naive_prime(x));
        }
    }
    long long l, r;
    cin >> l >> r;
    assert(1 <= l && l <= r);
    vector<char> is_prime = segmented_sieve(l, r);
    cout << count(is_prime.begin(), is_prime.end(), 1) << '\n';
}
