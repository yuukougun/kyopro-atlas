// ACL の floor_sum と、そこから作る 2 つの量：(a i + b) mod m の和と、(A k + B) mod M > k を満たす k の個数
// 入力：T、続いて T 行の n m a b（0 <= n < 2^32、1 <= m < 2^32、0 <= a, b < 2^32）
// 出力：各行に floor_sum、Σ (a i + b) mod m、0 <= k < n で (a k + b) mod m > k となる k の個数
#include <bits/stdc++.h>
#include <atcoder/math>
using namespace std;

// --8<-- [start:core]
// Σ_{i=0}^{n-1} (a i + b) mod m ＝ Σ (a i + b) − m Σ ⌊(a i + b)/m⌋（a, b >= 0）
// 途中はあふれうるが、unsigned の計算は mod 2^64 なので、答えが 2^64 未満なら正しい
unsigned long long sum_of_mod(long long n, long long m, long long a, long long b) {
    unsigned long long un = n;
    unsigned long long s = un * (un - 1) / 2 * a + un * b;  // n = 0 でも un * (un - 1) = 0
    return s - (unsigned long long)m * atcoder::floor_sum(n, m, a, b);
}

// 0 <= k < n で (a k + b) mod m > k となる k の個数（a, b >= 0）
long long count_mod_greater(long long n, long long m, long long a, long long b) {
    n = min(n, m);  // k >= m では余り < m <= k なので条件を満たさない
    // 余り <= k の k でだけ ⌊(a k + b)/m⌋ − ⌊((a−1) k + b − 1)/m⌋ が 1、ほかは 0
    // a − 1・b − 1 が負になっても ACL の floor_sum はそのまま受け付ける
    unsigned long long bad = (unsigned long long)atcoder::floor_sum(n, m, a, b)
                           - (unsigned long long)atcoder::floor_sum(n, m, a - 1, b - 1);
    return n - (long long)bad;
}
// --8<-- [end:core]

int main() {
    // 小さい値をすべて試して愚直解と一致することを確かめる
    for (long long n = 0; n <= 10; n++)
        for (long long m = 1; m <= 10; m++)
            for (long long a = 0; a <= 22; a++)
                for (long long b = 0; b <= 22; b++) {
                    long long fs = 0, sm = 0, cnt = 0;
                    for (long long k = 0; k < n; k++) {
                        fs += (a * k + b) / m;
                        sm += (a * k + b) % m;
                        if ((a * k + b) % m > k) cnt++;
                    }
                    assert(atcoder::floor_sum(n, m, a, b) == fs);
                    assert(sum_of_mod(n, m, a, b) == (unsigned long long)sm);
                    assert(count_mod_greater(n, m, a, b) == cnt);
                }

    int t;
    cin >> t;
    for (int q = 0; q < t; q++) {
        long long n, m, a, b;
        cin >> n >> m >> a >> b;
        cout << (unsigned long long)atcoder::floor_sum(n, m, a, b) << ' '
             << sum_of_mod(n, m, a, b) << ' ' << count_mod_greater(n, m, a, b) << '\n';
    }
}
