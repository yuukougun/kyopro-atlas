#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    vector<int> a{1, 2, 3};
    vector<int> b{10, 20, 30};
    for (auto [i, x] : a | views::enumerate) x *= 2;  // auto でも a が書き換わる
    for (auto [x, y] : views::zip(a, b)) y += x;      // b が書き換わる
    for (int x : a) cout << x << ' ';
    cout << '\n';  // 2 4 6
    for (int y : b) cout << y << ' ';
    cout << '\n';  // 12 24 36
    // --8<-- [end:core]
}
