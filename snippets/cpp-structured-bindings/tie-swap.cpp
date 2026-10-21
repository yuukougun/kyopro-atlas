#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:bad]
    int a = 1, b = 2;
    tie(a, b) = tie(b, a);  // a = b; b = a; の順になる
    cout << a << ' ' << b << '\n';  // 2 2
    // --8<-- [end:bad]
    // --8<-- [start:good]
    int c = 1, d = 2;
    tie(c, d) = pair{d, c};  // 右辺のコピーを先に作る
    cout << c << ' ' << d << '\n';  // 2 1
    swap(c, d);
    cout << c << ' ' << d << '\n';  // 1 2
    // --8<-- [end:good]
}
