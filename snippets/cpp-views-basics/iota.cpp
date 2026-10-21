#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    long long s = 0;
    for (int i : views::iota(0, n)) s += i;  // for (int i = 0; i < n; i++) と同じ
    cout << s << '\n';

    for (int i : views::iota(1) | views::take(3)) cout << i << ' ';  // 1 から始まる無限の列の先頭 3 個
    cout << '\n';
    // --8<-- [end:core]

    // iota(a, b) は a > b だと未定義なので、空にしたいときは a == b にする
    for (int i : views::iota(n, n)) cout << i;
    cout << "end\n";
}
