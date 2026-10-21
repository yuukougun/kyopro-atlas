#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a{3, 1, 4};
    // --8<-- [start:core]
    auto z = views::zip(a, views::iota(0));  // iota(0) に終わりがないので、begin と end の型が違う
    vector<pair<int, int>> p(z.begin(), z.end());  // コンパイルエラー
    // --8<-- [end:core]
    cout << p.size() << '\n';
}
