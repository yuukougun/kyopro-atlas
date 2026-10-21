#include <bits/stdc++.h>
using namespace std;

int main() {
    double x;
    cin >> x;
    // --8<-- [start:core]
    cout << (long long)(x * 100) << '\n';  // 0.29 なら 28（28.999… を切り捨てる）
    cout << llround(x * 100) << '\n';      // 0.29 なら 29（四捨五入）
    // --8<-- [end:core]
}
