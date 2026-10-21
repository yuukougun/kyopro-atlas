#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x;
    cin >> x;
    // --8<-- [start:core]
    cout << min(1, x) << '\n';  // コンパイルエラー：no matching function for call to 'min(int, long long int&)'
    // --8<-- [end:core]
}
