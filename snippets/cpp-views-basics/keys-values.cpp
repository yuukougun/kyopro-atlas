#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> cnt = {{"apple", 3}, {"banana", 1}, {"cherry", 2}};
    vector<tuple<int, int, int>> edges = {{0, 1, 5}, {1, 2, 7}};
    // --8<-- [start:core]
    for (const string& k : cnt | views::keys) cout << k << ' ';  // キーだけ
    cout << '\n';
    for (int c : cnt | views::values) cout << c << ' ';  // 値だけ
    cout << '\n';
    for (int w : edges | views::elements<2>) cout << w << ' ';  // tuple の 2 番目（0 から数える）だけ
    cout << '\n';
    // --8<-- [end:core]
    for (auto& c : cnt | views::values) c *= 10;  // 参照なので元の map が書き換わる
    cout << cnt["apple"] << '\n';
}
