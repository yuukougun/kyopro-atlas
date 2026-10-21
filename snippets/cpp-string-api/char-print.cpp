#include <bits/stdc++.h>
using namespace std;

int main() {
    int i = 1;
    // --8<-- [start:core]
    cout << 'a' + i << '\n';        // 98（char と int の和は int になる）
    cout << char('a' + i) << '\n';  // b
    // --8<-- [end:core]
}
