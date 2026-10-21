#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3};
    int calls = 0;
    // --8<-- [start:core]
    auto r = a | views::transform([&](int x) { calls++; return x * 2; });
    for (int y : r) cout << y << ' ';  // 2 4 6
    cout << '\n';
    a[0] = 10;                         // 元を書き換えると
    for (int y : r) cout << y << ' ';  // 20 4 6（view は値を覚えていない）
    cout << '\n';
    cout << calls << '\n';             // 6（回すたびに計算し直す）
    // --8<-- [end:core]
}
