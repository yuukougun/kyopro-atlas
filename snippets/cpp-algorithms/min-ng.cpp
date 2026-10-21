#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x = 5;
    // --8<-- [start:core]
    cout << min(1, x) << '\n';  // int と long long：コンパイルエラー
    // 直し方：min(1LL, x) か min<long long>(1, x)
    // --8<-- [end:core]
}
