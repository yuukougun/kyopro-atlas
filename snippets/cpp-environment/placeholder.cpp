#include <bits/stdc++.h>
using namespace std;
int main() {
    // --8<-- [start:core]
    auto [_, x] = pair{1, 2};
    auto [_, y] = pair{3, 4};  // 同じ場所で 2 回目の _（C++26 の機能）
    cout << x + y << '\n';
    // --8<-- [end:core]
}
