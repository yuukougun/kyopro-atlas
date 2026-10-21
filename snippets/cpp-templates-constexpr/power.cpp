#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T>
T power(T a, long long n) {  // a の n 乗（繰り返し二乗法）。T は呼ぶときに決まる
    T res = 1;
    while (n > 0) {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}
// --8<-- [end:core]

int main() {
    long long x;
    double y;
    int n;
    cin >> x >> y >> n;
    // --8<-- [start:call]
    cout << power(x, n) << '\n';          // T = long long
    cout << power(y, n) << '\n';          // T = double
    cout << power(2LL, 40) << '\n';       // T = long long：1099511627776
    static_assert(is_same_v<decltype(power(2, 40)), int>);  // 2 は int なので T = int
    // --8<-- [end:call]
    assert(power(3LL, 0) == 1);
}
