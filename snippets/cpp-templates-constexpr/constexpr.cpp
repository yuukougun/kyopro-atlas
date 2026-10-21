#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
constexpr long long MOD = 998244353;  // コンパイル時に決まる定数
constexpr int MAXN = 200'005;
int cnt[MAXN];  // 配列の大きさに使える

constexpr long long pow_mod(long long a, long long n) {  // 定数式の中でも、実行時にも呼べる
    long long res = 1;
    a %= MOD;
    while (n > 0) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}

constexpr auto TEN = [] {  // 10 の累乗の表を、その場で呼ぶラムダで作る
    array<long long, 19> t{};
    t[0] = 1;
    for (int i = 1; i < 19; i++) t[i] = t[i - 1] * 10;
    return t;
}();  // 最後の () で呼ぶ。TEN はラムダではなく、返した array

static_assert(TEN[18] == 1'000'000'000'000'000'000LL);  // コンパイル時に確かめる
static_assert(pow_mod(2, 23) == 8388608);
// --8<-- [end:core]

int main() {
    int k;
    long long n;
    cin >> k >> n;
    cout << TEN[k] << ' ' << pow_mod(3, n) << '\n';  // 実行時の値でも呼べる
    cnt[0]++;
}
