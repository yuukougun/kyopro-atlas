#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using u128 = unsigned __int128;

// --8<-- [start:is-prime]
// a * b mod m（積は 128 bit で計算する）
u64 mul_mod(u64 a, u64 b, u64 m) { return (u128)a * b % m; }

u64 pow_mod64(u64 a, u64 e, u64 m) {
    u64 res = 1 % m;
    a %= m;
    while (e > 0) {
        if (e & 1) res = mul_mod(res, a, m);
        a = mul_mod(a, a, m);
        e >>= 1;
    }
    return res;
}

// 2^64 未満で決定的な Miller-Rabin
bool is_prime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;  // 底が n の倍数なら何も分からないので飛ばす
        u64 x = pow_mod64(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool found_minus_one = false;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                found_minus_one = true;
                break;
            }
        }
        if (!found_minus_one) return false;  // a は n が合成数である証拠
    }
    return true;
}
// --8<-- [end:is-prime]

// --8<-- [start:rho]
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// 合成数 n（奇数）の 1 でも n でもない約数を 1 つ返す
u64 find_factor(u64 n) {
    while (true) {
        u64 c = rng() % (n - 1) + 1;
        auto f = [&](u64 x) { return (u64)(((u128)x * x + c) % n); };
        u64 x = rng() % n, y = x, g = 1;
        while (g == 1) {
            x = f(x);     // 1 歩進む
            y = f(f(y));  // 2 歩進む
            g = gcd(x > y ? x - y : y - x, n);
        }
        if (g != n) return g;  // g == n なら c を変えてやり直す
    }
}

void factor_rec(u64 n, vector<u64>& res) {
    if (n == 1) return;
    if (is_prime(n)) {
        res.push_back(n);
        return;
    }
    u64 g = find_factor(n);
    factor_rec(g, res);
    factor_rec(n / g, res);
}

vector<u64> factorize(u64 n) {
    vector<u64> res;
    for (u64 p = 2; p < 100 && p * p <= n; p++) {  // 小さい素因数は先に割る
        while (n % p == 0) {
            res.push_back(p);
            n /= p;
        }
    }
    factor_rec(n, res);
    sort(res.begin(), res.end());
    return res;
}
// --8<-- [end:rho]

// 試し割りと比べる
void self_check() {
    for (u64 n = 1; n <= 3000; n++) {
        vector<u64> naive;
        u64 m = n;
        for (u64 p = 2; p * p <= m; p++) {
            while (m % p == 0) {
                naive.push_back(p);
                m /= p;
            }
        }
        if (m > 1) naive.push_back(m);
        assert(factorize(n) == naive);
        assert(is_prime(n) == (naive.size() == 1));
    }
    // 底 2・7・61 をすべて通る合成数（4759123141 = 48781 × 97561）
    assert(!is_prime(4759123141ULL));
    // フェルマーの小定理の判定をすべての底で通る合成数（カーマイケル数）
    assert(!is_prime(561));
}

int main() {
    self_check();
    int q;
    cin >> q;
    while (q--) {
        u64 a;
        cin >> a;
        vector<u64> fs = factorize(a);
        cout << fs.size();
        for (u64 p : fs) cout << ' ' << p;
        cout << '\n';
    }
}
