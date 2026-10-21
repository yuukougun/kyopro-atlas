#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    int calls = 0;
    auto sq = [&](int x) { calls++; return x * x; };
    auto odd = [](int x) { return x % 2 == 1; };
    // --8<-- [start:core]
    // 先に filter：残った 3 個にだけ sq を呼ぶ
    calls = 0;
    for (int y : a | views::filter(odd) | views::transform(sq)) cout << y << ' ';
    cout << "/ " << calls << '\n';  // 1 9 25 / 3

    // 先に transform：filter の判定で 5 回、取り出しでさらに 3 回
    calls = 0;
    for (int y : a | views::transform(sq) | views::filter(odd)) cout << y << ' ';
    cout << "/ " << calls << '\n';  // 1 9 25 / 8
    // --8<-- [end:core]
}
