#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3, 4};
    // --8<-- [start:core]
    auto r = a | views::filter([](int x) { return x % 2 == 0; });
    for (int x : r) cout << x << ' ';  // 2 4
    cout << '\n';
    a[1] = 5;                          // 通った要素を条件に合わない値にする（未定義動作）
    for (int x : r) cout << x << ' ';  // 手元では 5 4（覚えた先頭の位置から始まる）
    cout << '\n';
    // --8<-- [end:core]
}
