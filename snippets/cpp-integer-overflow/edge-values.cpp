#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, w;
    cin >> a >> w;
    // --8<-- [start:core]
    const int INF = INT_MAX;
    cout << INF + w << '\n';                      // w = 1 で -2147483648（あふれ。未定義動作）
    const long long INF2 = 1LL << 60;
    cout << INF2 + INF2 << '\n';                  // 2305843009213693952（2^61。収まる）
    cout << abs(a) << ' ' << abs((long long)a) << '\n';  // a = INT_MIN で -2147483648 2147483648
    // --8<-- [end:core]
}
