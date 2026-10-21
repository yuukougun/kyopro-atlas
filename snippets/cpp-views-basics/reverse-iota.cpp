#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    for (int i : views::iota(0, n) | views::reverse) cout << i << ' ';  // n-1, ..., 1, 0
    cout << '\n';
    // --8<-- [end:core]
}
