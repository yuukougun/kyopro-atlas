#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a;
    cin >> a;
    __int128 x = (__int128)a * a;
    // --8<-- [start:core]
    cout << format("{}", x) << '\n';  // C++20 の format は __int128 を受ける（GCC 13〜）
    // --8<-- [end:core]
}
