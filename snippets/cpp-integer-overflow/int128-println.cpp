#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a;
    cin >> a;
    __int128 x = -(__int128)a * a;
    // --8<-- [start:core]
    println("{}", x);  // C++23 の println（GCC 14〜。g++-13 にはない）
    // --8<-- [end:core]
}
