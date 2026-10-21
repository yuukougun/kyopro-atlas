// floor sum を自分で書く：Σ_{i=0}^{n-1} ⌊(a i + b) / m⌋ を、互除法と同じ形のくり返しで O(log m) で求める
// 入力：T、続いて T 行の n m a b（0 <= n < 2^32、1 <= m < 2^32、0 <= a, b < 2^32）。各行の答えを出す
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// Σ_{i=0}^{n-1} ⌊(a i + b) / m⌋ を返す（答えがあふれたら mod 2^64 の値）
// 前提：n < 2^32、1 <= m < 2^32、a, b >= 0（a, b < m にしてから計算するので、途中の a * n + b は 2^64 未満）
unsigned long long floor_sum(unsigned long long n, unsigned long long m,
                             unsigned long long a, unsigned long long b) {
    unsigned long long ans = 0;
    while (true) {
        if (a >= m) {  // ⌊a/m⌋ i の部分を式で足し、a < m にする
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {  // ⌊b/m⌋ の部分を式で足し、b < m にする
            ans += n * (b / m);
            b %= m;
        }
        unsigned long long y_max = a * n + b;  // 直線の x = n での高さの m 倍
        if (y_max < m) break;                  // 直線の下に数える格子点がもうない
        // 縦と横を入れ替える：(n, m, a, b) → (⌊y_max/m⌋, a, m, y_max mod m)
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}
// --8<-- [end:core]

// 愚直解：i を全部回す（小さい値での比べ合わせ用）
unsigned long long floor_sum_naive(unsigned long long n, unsigned long long m,
                                   unsigned long long a, unsigned long long b) {
    unsigned long long s = 0;
    for (unsigned long long i = 0; i < n; i++) s += (a * i + b) / m;
    return s;
}

int main() {
    // 小さい値をすべて試して愚直解と一致することを確かめる
    for (unsigned long long n = 0; n <= 12; n++)
        for (unsigned long long m = 1; m <= 12; m++)
            for (unsigned long long a = 0; a <= 25; a++)
                for (unsigned long long b = 0; b <= 25; b++)
                    assert(floor_sum(n, m, a, b) == floor_sum_naive(n, m, a, b));
    // 乱数でもう少し大きい値を試す
    mt19937_64 rng(12345);
    for (int t = 0; t < 20000; t++) {
        unsigned long long n = rng() % 2000, m = rng() % 100000 + 1;
        unsigned long long a = rng() % 300000, b = rng() % 300000;
        assert(floor_sum(n, m, a, b) == floor_sum_naive(n, m, a, b));
    }

    int t;
    cin >> t;
    for (int q = 0; q < t; q++) {
        unsigned long long n, m, a, b;
        cin >> n >> m >> a >> b;
        cout << floor_sum(n, m, a, b) << '\n';
    }
}
