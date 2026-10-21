#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    // --8<-- [start:core]
    // a * b と c * d を比べる。a = b = 10^18、c = 10^18 + 1、d = 10^18 - 1 なら c * d = a * b - 1
    bool eq_ld = (long double)a * b == (long double)c * d;  // 1（丸められて「等しい」）
    bool eq_128 = (__int128)a * b == (__int128)c * d;       // 0（正しい）
    // --8<-- [end:core]
    cout << eq_ld << ' ' << eq_128 << '\n';
}
