#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:gcd]
// a, b は 0 以上
long long my_gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;  // gcd(a, b) = gcd(b, a mod b)
        a = b;
        b = r;
    }
    return a;  // gcd(a, 0) = a
}
// --8<-- [end:gcd]

// --8<-- [start:lcm]
// a, b は 1 以上。lcm(a, b) が limit を超えるなら -1 を返す
long long lcm_capped(long long a, long long b, long long limit) {
    long long x = a / my_gcd(a, b);  // 先に割る
    if (x > limit / b) return -1;    // x * b > limit を、掛けずに判定する
    return x * b;
}
// --8<-- [end:lcm]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    const long long LIMIT = 1'000'000'000'000'000'000LL;
    // --8<-- [start:many]
    long long g = 0;  // gcd(0, x) = x なので、gcd は 0 から始める
    long long l = 1;  // lcm(1, x) = x なので、lcm は 1 から始める
    for (long long x : a) {
        g = my_gcd(g, x);
        if (l != -1) l = lcm_capped(l, x, LIMIT);  // 一度超えたら -1 のまま
    }
    // --8<-- [end:many]
    long long g2 = 0;
    for (long long x : a) g2 = gcd(g2, x);
    assert(g == g2);
    cout << g << ' ' << l << '\n';
}
