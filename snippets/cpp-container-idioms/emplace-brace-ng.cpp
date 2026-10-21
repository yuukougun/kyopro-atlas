#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<pair<int, int>> e;
    // --8<-- [start:core]
    e.emplace_back({1, 2});  // コンパイルエラー：{1, 2} から引数の型を推論できない
    // --8<-- [end:core]
    cout << e.size() << '\n';
}
