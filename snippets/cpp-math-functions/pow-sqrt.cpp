#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long p1 = (long long)pow(3, 35);    // 50031545098999704（double を経るので末尾がずれる）
    long long p2 = 1;
    for (int i = 0; i < 35; i++) p2 *= 3;    // 50031545098999707（正しい）

    long long x = 999999999999999999LL;      // 10^18 - 1
    long long s1 = (long long)sqrt(x);       // 1000000000（1 大きい）
    long long s2 = (long long)sqrtl(x);      // 999999999（この x では正しい）
    // --8<-- [end:core]
    cout << p1 << ' ' << p2 << '\n' << s1 << ' ' << s2 << '\n';
}
