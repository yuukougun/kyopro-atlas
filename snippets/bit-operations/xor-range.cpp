#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 0 xor 1 xor ... xor n（n ≥ 0）。n mod 4 で決まる
long long xor_upto(long long n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}

// a xor (a + 1) xor ... xor b（0 ≤ a ≤ b）。[0, a) の分を打ち消す
long long xor_range(long long a, long long b) {
    if (a == 0) return xor_upto(b);
    return xor_upto(b) ^ xor_upto(a - 1);
}
// --8<-- [end:core]

int main() {
    // 素朴な計算と比べる
    long long acc = 0;
    for (long long n = 0; n <= 1000; n++) {
        acc ^= n;
        assert(xor_upto(n) == acc);
    }
    long long a, b;
    cin >> a >> b;
    cout << xor_range(a, b) << '\n';
}
