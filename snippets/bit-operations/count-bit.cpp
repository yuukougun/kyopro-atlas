#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 0 以上 n 以下の整数のうち、bit d が 1 のものの個数（0 ≤ n < 2^62）
long long count_bit(long long n, int d) {
    long long period = 1LL << (d + 1);  // bit d は長さ 2^(d+1) の周期で 0 が 2^d 個、1 が 2^d 個並ぶ
    long long full = (n + 1) / period;  // 完全な周期の数
    long long rest = (n + 1) % period;  // 最後の半端な周期の長さ
    return full * (1LL << d) + max(0LL, rest - (1LL << d));
}
// --8<-- [end:core]

int main() {
    // 素朴な数え方と比べる
    for (long long n = 0; n <= 300; n++) {
        for (int d = 0; d < 10; d++) {
            long long c = 0;
            for (long long k = 0; k <= n; k++) c += (k >> d) & 1;
            assert(count_bit(n, d) == c);
        }
    }
    long long n;
    int d;
    cin >> n >> d;
    cout << count_bit(n, d) << '\n';
}
