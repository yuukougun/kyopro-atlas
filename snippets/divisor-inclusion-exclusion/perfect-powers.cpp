// 約数包除で累乗数を数える：指数 b ごとの個数から、最大の指数がちょうど b のものを大きい b から求める
// 入力：n（1 <= n < 2^63）
// 出力：1 以上 n 以下で a^b（a >= 1, b >= 2）と書ける数の個数
#include <bits/stdc++.h>
using namespace std;

// a >= 1, k >= 1 のとき、a^k <= n かを、あふれずに判定する
bool pow_le(long long a, long long k, long long n) {
    if (a == 1) return 1 <= n;
    long long x = 1;
    for (long long i = 0; i < k; i++) {
        if (x > n / a) return false;
        x *= a;
    }
    return true;
}

// 0 <= n, k >= 1 のとき、a^k <= n となる最大の a（整数の K 乗根）
long long kth_root(long long n, long long k) {
    if (k == 1) return n;
    long long ok = 0, ng = 3037000500LL;
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        if (pow_le(mid, k, n)) ok = mid;
        else ng = mid;
    }
    return ok;
}

// --8<-- [start:core]
long long count_perfect_powers(long long n) {
    const int B = 62;  // n <= 10^18 なら 2^60 > n で指数は 59 までで足りるが、n < 2^63 まで正しいよう 62 まで回す
    vector<long long> h(B + 1, 0);  // h[b]：2 以上の数で、最大の指数がちょうど b のものの個数
    for (int b = B; b >= 2; b--) {
        h[b] = kth_root(n, b) - 1;  // F(b)：c^b（c >= 2）と書ける数の個数。1 は除く
        for (int k = 2 * b; k <= B; k += b) h[b] -= h[k];  // 最大の指数が 2b, 3b, … のものを引く
    }
    long long res = 1;  // 1 = 1^2 は別に数える
    for (int b = 2; b <= B; b++) res += h[b];
    return res;
}
// --8<-- [end:core]

int main() {
    // 小さい n を、集合で重複を除く素朴な数え方と比べる
    set<long long> s = {1};
    for (long long a = 2; a * a <= 200000; a++) {
        for (long long x = a * a; x <= 200000; x *= a) s.insert(x);
    }
    long long cnt = 0;
    for (long long v = 1; v <= 200000; v++) {
        if (s.count(v)) cnt++;
        assert(count_perfect_powers(v) == cnt);
    }

    long long n;
    cin >> n;
    cout << count_perfect_powers(n) << '\n';
}
