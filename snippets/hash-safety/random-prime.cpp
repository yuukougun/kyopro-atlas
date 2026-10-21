// 巨大な整数（10 進の文字列）を、実行時に乱択した素数の mod で比べる。
// 入力：N と N 個の正の整数（各 1000 桁程度まで）。A_i × A_j = A_k となる (i, j, k) の個数を出力する。
#include <bits/stdc++.h>
using namespace std;

unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m) { return (unsigned __int128)a * b % m; }
unsigned long long powmod(unsigned long long a, unsigned long long e, unsigned long long m) {
    unsigned long long r = 1;
    for (a %= m; e > 0; e >>= 1, a = mulmod(a, a, m))
        if (e & 1) r = mulmod(r, a, m);
    return r;
}
// 決定的な Miller-Rabin（2^64 未満ならこの 7 つの底で正しく判定できる）
bool is_prime(unsigned long long n) {
    if (n < 2) return false;
    for (unsigned long long p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (n % p == 0) return n == p;
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) d /= 2, s++;
    for (unsigned long long a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        unsigned long long x = powmod(a, d, n);
        if (x == 0 || x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 1; i < s && composite; i++) {
            x = mulmod(x, x, n);
            if (x == n - 1) composite = false;
        }
        if (composite) return false;
    }
    return true;
}

// --8<-- [start:core]
// [2^60, 2^61) から素数を乱択する。この範囲の素数は約 2.7×10^16 個あり、約 42 個に 1 個が素数
unsigned long long random_prime(mt19937_64& rng) {
    while (true) {
        unsigned long long p = (1ULL << 60) | (rng() & ((1ULL << 60) - 1));
        if (is_prime(p)) return p;
    }
}
// 10 進の文字列 s を p で割った余り（上の桁から 10 倍して足す）
unsigned long long mod_of(const string& s, unsigned long long p) {
    unsigned long long r = 0;
    for (char c : s) r = ((unsigned __int128)r * 10 + (c - '0')) % p;
    return r;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto& s : a) cin >> s;
    // --8<-- [start:usage]
    mt19937_64 rng(random_device{}());                    // 実行ごとに違う素数を選ぶ
    unsigned long long p = random_prime(rng), q = random_prime(rng);  // 独立に 2 つ
    vector<pair<unsigned long long, unsigned long long>> h(n);
    map<pair<unsigned long long, unsigned long long>, long long> cnt;  // ハッシュごとの個数
    for (int i = 0; i < n; i++) {
        h[i] = {mod_of(a[i], p), mod_of(a[i], q)};
        cnt[h[i]]++;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            pair<unsigned long long, unsigned long long> prod = {
                (unsigned long long)((unsigned __int128)h[i].first * h[j].first % p),
                (unsigned long long)((unsigned __int128)h[i].second * h[j].second % q)};
            auto it = cnt.find(prod);
            if (it != cnt.end()) ans += it->second;
        }
    // --8<-- [end:usage]
    bool small = true;  // どれも 9 桁以下なら、long long の積で素朴に数えて照らす
    for (auto& s : a) small &= s.size() <= 9;
    if (small) {
        long long naive = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) naive += stoll(a[i]) * stoll(a[j]) == stoll(a[k]);
        assert(ans == naive);
    }
    assert(is_prime(2) && is_prime((1ULL << 61) - 1) && !is_prime(561) && !is_prime(1ULL << 60));
    cout << ans << '\n';
}
