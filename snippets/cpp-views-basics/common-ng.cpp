#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {3, 1, -4, 1};
    // --8<-- [start:core]
    auto r = a | views::take_while([](int x) { return x > 0; });
    vector<int> b(r.begin(), r.end());  // コンパイルエラー：begin と end の型が違う
    // --8<-- [end:core]
    cout << b.size() << '\n';
}
