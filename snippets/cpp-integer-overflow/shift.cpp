#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long x = 1 << 40;    // 警告 -Wshift-count-overflow。手元では 0
    long long y = 1LL << 40;  // 1099511627776
    // --8<-- [end:core]
    cout << x << ' ' << y << '\n';
    // --8<-- [start:runtime]
    int k;
    cin >> k;
    long long z = 1 << k;  // k = 40 でも警告は出ない。手元では 256（2^(40 mod 32)）
    // --8<-- [end:runtime]
    cout << z << '\n';
}
