#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    long long p1 = static_cast<long long>(a) * b;  // a を広げてから掛ける
    long long p2 = (long long)a * b;               // 同じ意味（キャストは * より先に効く）
    long long p3 = 1LL * a * b;                    // 同じ意味（左から順に long long になる）
    // (long long)(a * b) は int のまま掛けてから広げるので、あふれた後では遅い
    cout << p1 << ' ' << p2 << ' ' << p3 << '\n';
    cout << (int)2.9 << ' ' << (int)-2.9 << '\n';  // 0 に向かって切り捨て：2 -2
    // --8<-- [end:core]
}
