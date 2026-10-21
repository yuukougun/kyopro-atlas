// mod を取らない C(n, k) の正確な値（答えが long long に収まる範囲。n ≤ 66 ならどの k でも収まる）。
// c = C(n, i) から C(n, i+1) = c × (n - i) / (i + 1) を、掛けてから割る順に作る。途中は __int128。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long binom_exact(long long n, long long k) {
    if (k < 0 || k > n) return 0;
    k = min(k, n - k);  // 掛ける回数を減らし、途中の値も小さくする
    __int128 c = 1;     // c = C(n, i)
    for (long long i = 0; i < k; i++) {
        c = c * (n - i) / (i + 1);  // 掛けてから割る（割り切れる）
    }
    return (long long)c;
}
// --8<-- [end:core]

int main() {
    long long n, k;
    cin >> n >> k;
    cout << binom_exact(n, k) << '\n';
}
