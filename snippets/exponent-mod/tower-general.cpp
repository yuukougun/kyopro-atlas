#include <bits/stdc++.h>
#include <atcoder/math>
using namespace std;

// φ(m) を試し割りで求める。O(√m)
long long euler_phi(long long m) {
    long long r = m;
    for (long long p = 2; p * p <= m; p++) {
        if (m % p != 0) continue;
        while (m % p == 0) m /= p;
        r -= r / p;
    }
    if (m > 1) r -= r / m;
    return r;
}

// --8<-- [start:core]
// a[0]^(a[1]^(...^a[k-1])) mod m を返す（a[i] >= 0、0^0 = 1、1 <= m <= 10^9）
long long tower_mod(const vector<long long>& a, long long m) {
    int k = a.size();
    const long long CAP = 1LL << 31;  // m より大きい上限
    // cap[i] = min(a[i]^(a[i+1]^(...)), CAP)：塔の本当の値を CAP で頭打ちにしたもの
    vector<long long> cap(k);
    cap[k - 1] = min(a[k - 1], CAP);
    for (int i = k - 2; i >= 0; i--) {
        long long e = cap[i + 1];
        if (a[i] <= 1) {
            cap[i] = (e == 0 ? 1 : a[i]);
            continue;
        }
        long long v = 1;
        for (long long t = 0; t < e && v < CAP; t++) v = min(v * min(a[i], CAP), CAP);
        cap[i] = v;
    }
    // solve(i, m) = a[i]^(a[i+1]^(...)) mod m
    auto solve = [&](auto&& self, int i, long long m) -> long long {
        if (m == 1) return 0;
        if (i == k - 1) return a[i] % m;
        long long ph = euler_phi(m);
        long long e = cap[i + 1];  // 指数の本当の値が φ(m) 未満なら、これが正確な値
        if (e >= ph) e = ph + self(self, i + 1, ph);  // φ(m) 以上なら φ(m) + (指数 mod φ(m))
        return atcoder::pow_mod(a[i], e, (int)m);
    };
    return solve(solve, 0, m);
}
// --8<-- [end:core]

int main() {
    assert(tower_mod({2, 3, 2}, 1000) == 512);  // 2^9
    assert(tower_mod({0, 0}, 7) == 1);         // 0^0
    assert(tower_mod({0, 0, 0}, 7) == 0);      // 0^(0^0) = 0^1
    int k;
    long long m;
    cin >> k >> m;
    vector<long long> a(k);
    for (int i = 0; i < k; i++) cin >> a[i];
    cout << tower_mod(a, m) << '\n';
}
