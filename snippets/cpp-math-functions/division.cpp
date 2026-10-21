#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    long long q = a / b;           // 0 に向かって切り捨てる（-7 / 2 は -3）
    long long r = a % b;           // 符号は a と同じ（-7 % 2 は -1）
    assert(q * b + r == a);        // この関係は必ず成り立つ
    bool odd = (a % 2 != 0);       // 奇数の判定は != 0 で書く（a % 2 == 1 は負の奇数で偽）
    // --8<-- [end:core]
    cout << q << ' ' << r << ' ' << odd << '\n';
}
