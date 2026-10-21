#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    cout << (long long)1e18 + 1 << '\n';    // 1000000000000000001：先に整数にしてから足す
    cout << (long long)(1e18 + 1) << '\n';  // 1000000000000000000：double で足すと +1 が消える
    long long INF1 = 1e18;  // long long に変換されて正確に 10^18
    auto INF2 = 1e18;       // double のまま
    cout << INF1 + 1 << ' ' << (INF2 + 1 == INF2) << '\n';  // 1000000000000000001 1
    // --8<-- [end:core]
}
