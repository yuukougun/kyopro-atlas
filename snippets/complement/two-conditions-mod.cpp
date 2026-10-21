#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long pow_mod(long long a, long long e) {
    long long r = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// --8<-- [start:core]
// 0 と 9 をどちらも含む、長さ n の数字の列の数（mod MOD）
long long count_both(long long n) {
    long long all = pow_mod(10, n);     // 全体
    long long no0 = pow_mod(9, n);      // 0 を含まない
    long long no9 = pow_mod(9, n);      // 9 を含まない
    long long none = pow_mod(8, n);     // 0 も 9 も含まない（2 回引いた分）
    long long ans = all - no0 - no9 + none;  // -2MOD < ans < 2MOD になりうる
    ans %= MOD;                          // C++ の % は負の値を負のまま返す
    if (ans < 0) ans += MOD;             // [0, MOD) に戻す
    return ans;
}
// --8<-- [end:core]

// 小さい n で全列挙して式を確かめる
long long brute(int n) {
    long long total = 1;
    for (int i = 0; i < n; i++) total *= 10;
    long long cnt = 0;
    for (long long x = 0; x < total; x++) {
        bool has0 = false, has9 = false;
        long long y = x;
        for (int i = 0; i < n; i++) {
            int d = y % 10;
            y /= 10;
            if (d == 0) has0 = true;
            if (d == 9) has9 = true;
        }
        if (has0 && has9) cnt++;
    }
    return cnt;
}

int main() {
    for (int n = 1; n <= 5; n++) assert(count_both(n) == brute(n));
    long long n;
    cin >> n;
    cout << count_both(n) << '\n';
}
