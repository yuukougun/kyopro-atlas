#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a >= 1, k >= 1 のとき、a^k <= n かを、あふれずに判定する
bool pow_le(long long a, long long k, long long n) {
    if (a == 1) return 1 <= n;
    long long x = 1;
    for (long long i = 0; i < k; i++) {
        if (x > n / a) return false;  // x * a > n。掛ける前に割り算で判定する
        x *= a;
    }
    return true;
}

// 0 <= n, k >= 1 のとき、a^k <= n となる最大の a を返す
long long kth_root(long long n, long long k) {
    if (k == 1) return n;
    long long ok = 0, ng = 3037000500LL;  // k >= 2 なら答えは √(2^63) 未満
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        if (pow_le(mid, k, n)) ok = mid;
        else ng = mid;
    }
    return ok;
}
// --8<-- [end:core]

int main() {
    // 小さい値を素朴な定義と比べる
    for (long long n = 0; n <= 3000; n++) {
        for (long long k = 1; k <= 12; k++) {
            long long a = 0;
            while (true) {
                long long p = 1;
                for (int i = 0; i < k; i++) p *= a + 1;
                if (p > n) break;
                a++;
            }
            assert(kth_root(n, k) == a);
        }
    }
    assert(kth_root(LLONG_MAX, 63) == 1);
    assert(kth_root(LLONG_MAX, 62) == 2);
    assert(kth_root(1, 1000000000) == 1);

    int q;
    cin >> q;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        cout << kth_root(n, k) << '\n';
    }
}
