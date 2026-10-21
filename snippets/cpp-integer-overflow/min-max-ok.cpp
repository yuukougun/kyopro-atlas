#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x;
    cin >> x;
    // --8<-- [start:core]
    long long a = min(1LL, x);             // 定数の型を合わせる
    long long b = min<long long>(1, x);    // 型を明示する（1 は long long に直される）
    long long c = max({0LL, x, 2 * x});    // 初期化子リストでも型をそろえる
    // --8<-- [end:core]
    cout << a << ' ' << b << ' ' << c << '\n';
}
