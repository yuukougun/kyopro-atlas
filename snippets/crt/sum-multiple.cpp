#include <bits/stdc++.h>
#include <atcoder/math>
using namespace std;

// 1 + 2 + ... + k が n の倍数になる最小の正の整数 k
long long solve(long long n) {
    long long n2 = 2 * n;  // k(k + 1) が 2n の倍数になる最小の k を求める
    // 2n を素因数分解し、素因数ごとの冪 p^e を並べる
    vector<long long> pw;
    long long rest = n2;
    for (long long p = 2; p * p <= rest; p++) {
        if (rest % p != 0) continue;
        long long q = 1;
        while (rest % p == 0) rest /= p, q *= p;
        pw.push_back(q);
    }
    if (rest > 1) pw.push_back(rest);
    int s = pw.size();
    long long best = LLONG_MAX;
    // --8<-- [start:core]
    // k と k + 1 は互いに素なので、各 p^e は k か k + 1 の片方だけを割る。
    // 2n = a * b（a は k を、b は k + 1 を割る）の分け方を bit 全探索する
    for (int bit = 0; bit < (1 << s); bit++) {
        long long a = 1, b = 1;
        for (int i = 0; i < s; i++) {
            if (bit >> i & 1) a *= pw[i];
            else b *= pw[i];
        }
        // k ≡ 0 (mod a) かつ k ≡ -1 (mod b)。a と b は互いに素なので必ず解がある
        auto [y, z] = atcoder::crt({0, -1}, {a, b});  // 負の余りも渡せる
        long long k = (y == 0 ? z : y);  // 欲しいのは正の k なので、0 なら z に直す
        best = min(best, k);
    }
    // --8<-- [end:core]
    return best;
}

int main() {
    // 小さい n で素朴な方法と一致することを確かめる
    for (long long n = 1; n <= 300; n++) {
        long long k = 1;
        while (k * (k + 1) / 2 % n != 0) k++;
        assert(solve(n) == k);
    }
    long long n;
    cin >> n;
    cout << solve(n) << '\n';
}
