#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    double x = 0.1 + 0.2;
    cout << (x == 0.3) << '\n';              // 0：0.30000000000000004 になっている
    cout << (abs(x - 0.3) < 1e-9) << '\n';   // 1：差が小さければ等しいとみなす
    long long y = 1 + 2;                      // 10 倍して整数で持てば正確
    cout << (y == 3) << '\n';                 // 1
    // --8<-- [end:core]
}
