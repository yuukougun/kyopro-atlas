#include <bits/stdc++.h>
using namespace std;

pair<int, int> divmod(int a, int b) { return {a / b, a % b}; }

int main() {
    // --8<-- [start:core]
    int q, r;
    tie(q, r) = divmod(17, 5);       // 既にある変数 q・r にまとめて代入
    cout << q << ' ' << r << '\n';   // 3 2
    tie(q, ignore) = divmod(9, 4);   // 要らない側は ignore で捨てる
    cout << q << '\n';               // 2

    int x1 = 1, y1 = 5, x2 = 1, y2 = 3;
    cout << (tie(x1, y1) < tie(x2, y2)) << '\n';  // 0（x が等しく y1 > y2）
    // --8<-- [end:core]
}
