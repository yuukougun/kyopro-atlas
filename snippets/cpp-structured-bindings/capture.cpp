#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    pair<int, int> p{3, 4};
    auto [w, h] = p;
    auto inside = [&](int x, int y) {  // w・h をキャプチャする（C++20）
        return 0 <= x && x < w && 0 <= y && y < h;
    };
    cout << inside(2, 3) << inside(3, 0) << '\n';  // 10

    tuple<int, int, int> t{1, 2, 3};
    auto [_, mid, last] = t;  // 使わない要素に _ を付ける（1 個だけなら C++17 から通る）
    cout << mid + last << '\n';  // 5
    // --8<-- [end:core]
}
