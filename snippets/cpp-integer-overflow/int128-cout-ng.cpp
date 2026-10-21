#include <bits/stdc++.h>
using namespace std;

int main() {
    __int128 x = 1;
    // --8<-- [start:core]
    cout << x << '\n';  // コンパイルエラー：ambiguous overload for 'operator<<'
    // --8<-- [end:core]
}
