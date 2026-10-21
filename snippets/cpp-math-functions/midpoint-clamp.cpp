#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, x;
    cin >> a >> b >> x;
    // --8<-- [start:core]
    int m1 = midpoint(a, b);   // a + (b - a) / 2 と同じ向きに丸める。a + b があふれても正しい
    int m2 = midpoint(b, a);   // 端数は第 1 引数の側に丸める
    int c = clamp(x, 0, 10);   // x を閉区間 [0, 10] に収める。min(max(x, 0), 10) と同じ
    // --8<-- [end:core]
    cout << m1 << ' ' << m2 << ' ' << c << '\n';
}
