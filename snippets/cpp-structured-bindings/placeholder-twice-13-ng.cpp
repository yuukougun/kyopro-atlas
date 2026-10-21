#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    tuple<int, int, int> t{1, 2, 3};
    auto [_, x, _] = t;  // g++-13 では _ の再宣言としてコンパイルエラー
    // --8<-- [end:core]
    cout << x << '\n';
}
