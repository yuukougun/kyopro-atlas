#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a^x ≡ b (mod m) となる最小の x ≥ 0。なければ −1。m は 2^31 未満
// 期待 O(√m)（ハッシュ表）。gcd(a, m) ≠ 1 でもよい
long long discrete_log(long long a, long long b, long long m) {
    if (m == 1) return 0;
    a %= m;
    b %= m;
    // coef · a^x ≡ b (mod m) の形を保ち、gcd(a, m) = 1 になるまで両辺を割る
    long long coef = 1, k = 0;
    while (true) {
        if (coef == b) return k;  // x = k が解（最小の解はここで見つかる）
        long long g = gcd(a, m);
        if (g == 1) break;
        if (b % g != 0) return -1;
        m /= g;
        b /= g;
        coef = coef * (a / g) % m;
        k++;
    }
    // ここからは gcd(a, m) = 1 で、coef · a^y ≡ b となる最小の y ≥ 1 を探す
    long long n = 1;
    while (n * n < m) n++;  // n = ⌈√m⌉
    // baby step：b · a^j → j（0 ≤ j < n）。同じ値なら大きい j で上書きする
    unordered_map<long long, long long> table;
    table.reserve(n * 2);
    long long cur = b;
    for (long long j = 0; j < n; j++) {
        table[cur] = j;
        cur = cur * a % m;
    }
    long long an = 1;  // a^n
    for (long long j = 0; j < n; j++) an = an * a % m;
    // giant step：coef · a^(i·n) を i = 1, 2, ..., n の順に引く
    cur = coef;
    for (long long i = 1; i <= n; i++) {
        cur = cur * an % m;
        auto it = table.find(cur);
        if (it != table.end()) return k + i * n - it->second;  // y = i·n − j
    }
    return -1;
}
// --8<-- [end:core]

int main() {
    // 小さい法のすべての (a, b) で、x を 0 から順に試す素朴な方法と比べる
    for (long long m = 1; m <= 120; m++) {
        for (long long a = 0; a < m; a++) {
            vector<long long> first(m, -1);
            long long v = 1 % m;
            for (long long x = 0; x <= 2 * m; x++) {
                if (first[v] == -1) first[v] = x;
                v = v * a % m;
            }
            for (long long b = 0; b < m; b++) assert(discrete_log(a, b, m) == first[b]);
        }
    }
    long long a, b, m;
    cin >> a >> b >> m;
    cout << discrete_log(a, b, m) << '\n';
}
