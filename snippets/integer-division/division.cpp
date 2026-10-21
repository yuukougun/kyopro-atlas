// 負の数でも正しい床関数・天井関数・非負の余り。各行の a b について
// floor_div(a, b)・ceil_div(a, b) と、b > 0 なら safe_mod(a, b) を出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// ⌊a / b⌋（b ≠ 0）。C++ の / は 0 に向かって切り捨てるので、
// 割り切れず商が負（a と b の符号が違う）のときだけ 1 引く
long long floor_div(long long a, long long b) {
    long long q = a / b;
    if (a % b != 0 && ((a < 0) != (b < 0))) q--;
    return q;
}

// ⌈a / b⌉（b ≠ 0）。割り切れず商が正（a と b の符号が同じ）のときだけ 1 足す
long long ceil_div(long long a, long long b) {
    long long q = a / b;
    if (a % b != 0 && ((a < 0) == (b < 0))) q++;
    return q;
}

// a mod m を 0 以上 m 未満で返す（m > 0）
long long safe_mod(long long a, long long m) {
    long long r = a % m;
    if (r < 0) r += m;
    return r;
}
// --8<-- [end:core]

int main() {
    long long a, b;
    while (cin >> a >> b) {
        assert(b != 0);
        long long f = floor_div(a, b), c = ceil_div(a, b);
        assert(f <= c && c - f <= 1);
        assert((c - f == 0) == (a % b == 0));
        if (b > 0) {
            long long r = safe_mod(a, b);
            assert(0 <= r && r < b);
            assert(f == (a - r) / b);  // a = b⌊a/b⌋ + (a mod b)
            cout << f << ' ' << c << ' ' << r << '\n';
        } else {
            cout << f << ' ' << c << '\n';
        }
    }
}
