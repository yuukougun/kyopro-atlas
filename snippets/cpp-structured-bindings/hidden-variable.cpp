#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    pair<int, int> p{1, 2};
    {
        auto [a, b] = p;   // auto e = p; の e（コピー）の first・second に名前を付ける
        a = 100;           // e.first が変わるだけ
    }
    cout << p.first << '\n';  // 1
    {
        auto& [a, b] = p;  // auto& e = p; の e（p そのもの）に名前を付ける
        a = 100;           // p.first が変わる
    }
    cout << p.first << '\n';  // 100
    // --8<-- [end:core]
}
