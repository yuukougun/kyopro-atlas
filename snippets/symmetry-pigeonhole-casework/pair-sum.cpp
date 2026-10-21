#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// --8<-- [start:core]
// i < j の組の積 a_i a_j の和を mod で求める（a_i ≥ 0）。
// 全体の和の 2 乗には (i, j) と (j, i) が 1 回ずつ、i = j の項が 1 回入る。
long long pair_sum(const vector<long long>& a) {
    long long s1 = 0, s2 = 0;
    for (long long x : a) {
        x %= MOD;
        s1 = (s1 + x) % MOD;
        s2 = (s2 + x * x) % MOD;
    }
    long long inv2 = (MOD + 1) / 2;                  // 2 の逆元
    long long all = (s1 * s1 % MOD - s2 + MOD) % MOD;  // 対角を引く（負にしない）
    return all * inv2 % MOD;                         // 2 で割る代わりに逆元を掛ける
}

// 割り算を使わない書き方：j の左にある a_i の和を a_j に掛けて足す
long long pair_sum_prefix(const vector<long long>& a) {
    long long ans = 0, left = 0;
    for (long long x : a) {
        x %= MOD;
        ans = (ans + left * x) % MOD;
        left = (left + x) % MOD;
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long p = pair_sum(a);
    assert(p == pair_sum_prefix(a));
    cout << p << '\n';
}
