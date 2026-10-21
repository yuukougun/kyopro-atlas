#include <bits/stdc++.h>
using namespace std;

// C++17 モードでも、g++-13・g++-15 は構造化束縛した名前のキャプチャを警告なしで通す
int main() {
    pair<int, int> p{3, 4};
    auto [w, h] = p;
    auto f = [w] { return w; };
    auto g = [&h] { return h; };
    cout << f() + g() << '\n';
}
