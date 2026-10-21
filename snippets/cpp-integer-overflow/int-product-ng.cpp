#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    long long p = a * b;  // int どうしで掛けてから long long に入れる。掛けた時点であふれる
    cout << p << '\n';    // a = b = 100000 で 1410065408（手元の g++-13・g++-15）
    // --8<-- [end:core]
}
