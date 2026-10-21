// double を経た割り算は 10^18 付近で誤る。整数の / と比べる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long a = 999999999999999999LL;  // 10^18 − 1
    long long b = 10;
    long long by_int = a / b;                             // 99999999999999999（正しい）
    long long by_double = (long long)floor((double)a / b);  // 100000000000000000（1 ずれる）
    cout << by_int << '\n' << by_double << '\n';
    // --8<-- [end:core]
    assert(by_int != by_double);
}
