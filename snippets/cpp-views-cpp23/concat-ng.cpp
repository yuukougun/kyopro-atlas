#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a{1, 2}, b{3};
    // --8<-- [start:core]
    for (int x : views::concat(a, b)) cout << x;  // -std=gnu++23 ではコンパイルエラー（C++26）
    // --8<-- [end:core]
    cout << '\n';
}
