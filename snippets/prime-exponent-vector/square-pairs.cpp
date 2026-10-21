#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// x（1 以上）の平方因子を除いた核：指数が奇数の素数の積
long long squarefree_kernel(long long x) {
    long long k = 1;
    for (long long p = 2; p * p <= x; p++) {
        int e = 0;
        while (x % p == 0) {
            x /= p;
            e++;
        }
        if (e % 2 == 1) k *= p;
    }
    if (x > 1) k *= x;  // 残った x は指数 1 の素数
    return k;
}

// a[i] × a[j]（i < j）が平方数になる組の個数
long long count_square_pairs(const vector<long long>& a) {
    long long n = a.size(), zero = 0;
    map<long long, long long> cnt;  // 核 → 個数
    for (long long x : a) {
        if (x == 0) zero++;
        else cnt[squarefree_kernel(x)]++;
    }
    long long res = 0;
    for (auto [k, c] : cnt) res += c * (c - 1) / 2;    // 核が等しい組
    res += zero * (n - zero) + zero * (zero - 1) / 2;  // 0 を含む組
    return res;
}
// --8<-- [end:core]

int main() {
    assert(squarefree_kernel(1) == 1);
    assert(squarefree_kernel(72) == 2);   // 72 = 2^3 × 3^2
    assert(squarefree_kernel(360) == 10); // 360 = 2^3 × 3^2 × 5
    assert(squarefree_kernel(97) == 97);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << count_square_pairs(a) << '\n';
}
