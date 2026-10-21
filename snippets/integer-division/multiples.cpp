// 閉区間 [L, R] にある K の倍数の個数と、x 以上で m で割って r 余る最小の数。
// 入力：L R K x m r（L ≤ R、K ≥ 1、m ≥ 1、0 ≤ r < m）
#include <bits/stdc++.h>
using namespace std;

long long floor_div(long long a, long long b) {
    long long q = a / b;
    if (a % b != 0 && ((a < 0) != (b < 0))) q--;
    return q;
}

long long safe_mod(long long a, long long m) {
    long long r = a % m;
    if (r < 0) r += m;
    return r;
}

// --8<-- [start:core]
// 閉区間 [L, R] にある K の倍数の個数（K ≥ 1。L が 0 や負でもよい）
long long count_multiples(long long L, long long R, long long K) {
    return floor_div(R, K) - floor_div(L - 1, K);
}

// x 以上で、m で割って r 余る最小の数（m ≥ 1、0 ≤ r < m）
long long next_with_rem(long long x, long long m, long long r) {
    return x + safe_mod(r - x, m);  // x から d（0 ≤ d < m）進めて余りを r にそろえる
}
// --8<-- [end:core]

int main() {
    long long L, R, K, x, m, r;
    while (cin >> L >> R >> K >> x >> m >> r) {
        assert(L <= R && K >= 1 && m >= 1 && 0 <= r && r < m);
        long long c = count_multiples(L, R, K);
        long long y = next_with_rem(x, m, r);
        assert(y >= x && y - x < m && safe_mod(y, m) == r);
        cout << c << ' ' << y << '\n';
    }
}
