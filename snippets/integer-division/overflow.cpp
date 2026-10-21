// 積があふれる前に割り算で判定する。N 個の正の整数の積と lcm を、
// 上限 LIM = 10^18 を超えたら -1 として出力する。
#include <bits/stdc++.h>
using namespace std;

const long long LIM = 1000000000000000000LL;  // 10^18

// --8<-- [start:core]
// a × b を返す。ただし LIM を超えるなら LIM + 1 を返す（a, b ≥ 1、LIM + 1 は long long に収まる）
long long mul_cap(long long a, long long b) {
    if (a > LIM / b) return LIM + 1;  // a × b > LIM ⟺ a > ⌊LIM / b⌋
    return a * b;
}

// lcm(a, b) を返す。LIM を超えるなら LIM + 1（a, b ≥ 1）
long long lcm_cap(long long a, long long b) {
    long long g = gcd(a, b);
    return mul_cap(a / g, b);  // a × b / g は a × b であふれるので、先に割ってから掛ける
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    long long prod = 1, l = 1;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        assert(1 <= a && a <= LIM);
        if (prod <= LIM) prod = mul_cap(prod, a);  // 一度超えたら LIM + 1 のまま
        if (l <= LIM) l = lcm_cap(l, a);
    }
    cout << (prod > LIM ? -1 : prod) << ' ' << (l > LIM ? -1 : l) << '\n';
}
