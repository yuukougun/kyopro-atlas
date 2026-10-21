#include <bits/stdc++.h>
using namespace std;

int main() {
    int s;
    cin >> s;
    // --8<-- [start:core]
    int a = popcount((unsigned)s);            // int と同じ 32 桁で数える
    int b = popcount((unsigned long long)s);  // 負の s は上位 32 桁も 1 で埋まる
    // --8<-- [end:core]
    cout << a << ' ' << b << '\n';
}
