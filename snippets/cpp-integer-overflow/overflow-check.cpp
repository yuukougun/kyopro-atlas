#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    const long long L = 1'000'000'000'000'000'000LL;  // 10^18
    // --8<-- [start:core]
    // 1. __builtin_mul_overflow：積が long long に収まらなければ true（GCC の拡張）
    long long r;
    bool over = __builtin_mul_overflow(a, b, &r);
    bool le1 = !over && r <= L;
    // 2. 割り算で比べる（a, b ≥ 1 のとき a * b <= L ⇔ a <= L / b）
    bool le2 = a <= L / b;
    // 3. __int128 で掛けてから比べる
    bool le3 = (__int128)a * b <= L;
    // --8<-- [end:core]
    assert(le1 == le2 && le2 == le3);
    cout << over << ' ' << le1 << '\n';
}
